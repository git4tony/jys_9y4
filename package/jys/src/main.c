#include <stdio.h>
#include <errno.h>
#include <modbus.h>

int main(int argc, char *argv[])
{
	modbus_t *ctx;
	struct timeval response_timeout = {1, 500000};
	struct timeval byte_timeout = {1, 500000};
	
	//uint16_t register_set[2] = {0};
	int reg_addr = 0;
	uint16_t data;

	ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'E', 8, 1);
	if ( ctx == NULL ) {
		fprintf(stderr, "Unable to create the libmodbus context\n");
		return -1;
	}

	if ( modbus_connect(ctx) == -1 ) {
		fprintf(stderr, "Modbus serial connection failed: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -2;
    	}
		
	modbus_set_byte_timeout(ctx, &response_timeout);
	modbus_set_response_timeout(ctx, &byte_timeout);

	//modbus_get_byte_timeout(ctx, &byte_timeout);
	//modbus_get_response_timeout(ctx, &response_timeout);
	//printf("Byte Timeout: %d seconds %d microseconds",byte_timeout.tv_sec, byte_timeout.tv_usec);
	//printf("Response Timeout: %d seconds %d microseconds\n",response_timeout.tv_sec, response_timeout.tv_usec);

	if ( modbus_set_slave(ctx, 1) == -1 ) {
		fprintf(stderr, "Modbus modbus_set_slave() failed: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -3;
	}	
		
	if ( argc == 2 ) {
		reg_addr = atoi(argv[1]);	
		if ( modbus_read_registers(ctx, reg_addr, 1, &data) == -1) {
			fprintf(stderr, "Slave Read failed: %s\n", modbus_strerror(errno));
			modbus_free(ctx);
			return -4;
		}
		fprintf(stdout, "%d\n", data); 
	}

	modbus_close(ctx);
	modbus_free(ctx);

	return 0;
}
