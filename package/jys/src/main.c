#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>  
#include <modbus.h>

typedef struct {
	uint16_t addr;
	const char *name;
	const char *descr;
	uint16_t len;
	enum {
		DEFAULT = 0,
		VOLT,
		AMP,
		WATT,
		FACTOR,
		HERTZ,
		WH,
		VARH
	} type;
	int min;
} reg_t;

const reg_t jys_9y4_registers[] = {
{40001, "", "Not Use", 1, 0, 0},
{40002, "net", "Connection Mode", 1, 0, 0},
{40003, "CT", "Current Ratio", 1, 0, 0},
{40004, "PT", "Voltage Ratio", 1, 0, 0},
{40005, "DI-S", "The First Three Rows Power Display Option", 1, 0, 0},
{40006, "DI-E", "Electricity Option", 1, 0, 0},
{40007, "DI-L", "Backlit Display Option", 1, 0, 0},
{40008, "FULL", "Rated Load Setting", 1, 0, 0},
{40009, "Addr", "The Machine Address", 1, 0, 0},
{40010, "Baud", "Baud Rate", 1, 0, 0},
{40011, "Data", "Data Format", 1, 0, 0},
{40012, "DO-1", "The First Way Switch Channel Selection", 1, 0, 0},
{40013, "UAH1", "The First Alarm Pick Up Value Set", 1, 0, 0},
{40014, "UAL1", "The First Alarm Drop Out Value Set", 1, 0, 0},
{40015, "DO-2", "The Second Way Switch Channel Selection", 1, 0, 0},
{40016, "UAH2", "The Second Alarm Pick Up Value Set", 1, 0, 0},
{40017, "UAL2", "The Second Alarm Drop Out Value Set", 1, 0, 0},
{40018, "DO-2", "The Third Way Switch Channel Selection", 1, 0, 0},
{40019, "UAH2", "The Third Way Switch Channel Selection", 1, 0, 0},
{40020, "UAL2", "The Third Alarm Drop Out Value Set", 1, 0, 0},
{40021, "DO-2", "The Fourth Way Switch Channel Selection", 1, 0, 0},
{40022, "UAH2", "The Fourth Alarm Pick Up Value Set", 1, 0, 0},
{40023, "UAL2", "The Fourth Alarm Drop Out Value Set", 1, 0, 0},
{40024, "AO-1", "The First Way Transmission Channel Selection", 1, 0, 0},
{40025, "ObL1", "The First Way Transmission Output Lower Limit", 1, 0, 0},
{40026, "Obh1", "The First Way Transmission Output Upper Limit", 1, 0, 0},
{40027, "AO-2", "The Second Way Transmission Channel Selection", 1, 0, 0},
{40028, "ObL2", "The Second way Transmission Output Lower Limit", 1, 0, 0},
{40029, "Obh2", "The Second way Transmission Output Upper Limit", 1, 0, 0},
{40030, "AO-3", "The Third Way Transmission Channel Selection", 1, 0, 0},
{40031, "ObL3", "The Third Way Transmission Output Lower Limit", 1, 0, 0},
{40032, "Obh3", "The Third Way Transmission Output Upper Limit", 1, 0, 0},
{40033, "AO-4", "The Fourth Way Transmission Channel Selection", 1, 0, 0},
{40034, "ObL4", "The Fourth Way Transmission Output Lower Limit", 1, 0, 0},
{40035, "Obh4", "The Fourth Way Transmission Output Upper Limit", 1, 0, 0},

{40122, "Un", "Zero-Sequence Voltage", 1, VOLT, 0},
{40129, "Ua", "A Phase Voltage", 1, VOLT, 1},
{40130, "Ub", "B Phase Voltage", 1, VOLT, 0},
{40131, "Uc", "C Phase Voltage", 1, VOLT, 0},
{40132, "Uab", "AB Wire Voltage", 1, VOLT, 0},
{40133, "Ubc", "BC Wire Voltage", 1, VOLT, 0},
{40134, "Uca", "CA Wire Voltage", 1, VOLT, 0},
{40135, "Ia", "A Phase Current", 1, AMP, 1},
{40136, "Ib", "B Phase Current", 1, AMP, 0},
{40137, "Ic", "C Phase Current", 1, AMP, 0},
{40138, "Pa", "A Phase Active Power", 1, WATT, 1},
{40139, "Pb", "B Phase Active Power", 1, WATT, 0},
{40140, "Pc", "C Phase Active Power", 1, WATT, 0},
{40141, "Qa", "A Phase Reactive Power", 1, WATT, 1},
{40142, "Qb", "B Phase Reactive Power", 1, WATT, 0},
{40143, "Qc", "C Phase Reactive Power", 1, WATT, 0},
{40144, "Sa", "A Phase Apparent Power", 1, WATT, 1},
{40145, "Sb", "B Phase Apparent Power", 1, WATT, 0},
{40146, "Sc", "C Phase Apparent Power", 1, WATT, 0},
{40147, "PS", "The Conjunction of Active Power", 1, WATT, 0},
{40148, "QS", "The Conjunction of Reactive Power", 1, WATT, 0},
{40149, "SS", "The Conjunction of Apparent Power", 1, WATT, 0},
{40150, "PFa", "A Phase Power Factor", 1, FACTOR, 1},
{40151, "PFb", "B Phase Power Factor", 1, FACTOR, 0},
{40152, "PFc", "C Phase Power Factor", 1, FACTOR, 0},
{40153, "PFS", "Total Power Factor", 1, FACTOR, 0},
{40154, "HZ", "Frequency", 1, HERTZ, 1},
{40155, "", "A, B Two Phase Power Parameters Sign", 1, 0, 0},
{40156, "", "C Phase and Phase Apparent Power Parameters Sign", 1, 0, 0},
{40157, "", "A, B, C and Phase Combined Power Factors Sign", 1, 0, 0},
{40158, "", "Four Way Switch Amount Output’s State", 1, 0, 0},
{40159, "", "Four Way Switch Amount Input’s State", 1, 0, 0},

{40161, "WPP", "Positive Active Energy", 2, WH, 1},
{40163, "WPN", "Reverse Active Energy", 2, WH, 0},
{40165, "WQP", "Positive Reactive Energy", 2, VARH, 0},
{40167, "WQN", "Reverse Reactive Energy", 2, VARH, 0},
};

char *format_value(int type, uint16_t *data)
{
	static char buf[80];

	switch(type) {
	case VOLT:
	case AMP:
	case HERTZ:
		sprintf(buf, "%d.%02u", data[0] / 100, data[0] % 100);
		break;
	case FACTOR:
		sprintf(buf, "%d.%03u", data[0] / 1000, data[0] % 1000);
		break;
	case WH:
	case VARH:
		{
			uint32_t value;

			value = data[0];
			value <<= 16;
			value |= data[1];
			sprintf(buf, "%lu", value);
		}
		break;
	case WATT:
	default:
		sprintf(buf, "%u", data[0]);
		break;
	}
	
	return buf;
}


int main(int argc, char *argv[])
{
	char *base_name;
	modbus_t *ctx;
	
	int opt;
	int get_all = 0;
	char *dev = "/dev/ttyUSB0";
	long baud_rate = 9600;
	char parity = 'E';
	int stop_bit = 1;

	while ((opt = getopt(argc, argv, "ad:b:p:s:h")) != -1) {
		switch (opt) {
			case 'a':
				get_all = 1;
				break;
			case 'd':
				dev = optarg;
				break;
			case 'b':
				baud_rate = atol(optarg);
				break;
			case 'p':
				parity = optarg[0];
				break;
			case 's':
				stop_bit = atoi(optarg);
				break;
			case 'h':
			default:
				base_name = basename(argv[0]);

				fprintf(stderr, "Usage: %s [-d /dev/ttyUSB0] [-b 9600] [-p E] [-s 1] [-a]\n"
						"       %s 40001 [num]\n"
						"-b baud_rate\n"
						"-p parity N,O,E\n"
						"-s stop_bit\n"
						"-a all\n",
					base_name, base_name);
					return -1;
		}
	}

	switch ( baud_rate ) {
		case 4800:
		case 9600:
		case 19200:
		case 38400:
		case 115200:
			break;
		default:
			baud_rate = 9600;
			break;
	}

	switch ( parity ) {
		case 'N':
		case 'n':
			parity = 'N';
			break;
		case 'O':
		case 'o':
			parity = 'O';
			break;
		default:
			parity = 'E';
			break; 
	}
		
	ctx = modbus_new_rtu(dev, baud_rate, parity, 8, stop_bit);
	if ( ctx == NULL ) {
		fprintf(stderr, "Unable to create the libmodbus context\n");
		return -2;
	}

	if ( modbus_connect(ctx) == -1 ) {
		fprintf(stderr, "Modbus serial connection failed: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -2;
    	}
		
	modbus_set_byte_timeout(ctx, 1, 500000);
	modbus_set_response_timeout(ctx, 1, 500000);

	if ( modbus_set_slave(ctx, 1) == -1 ) {
		fprintf(stderr, "Modbus modbus_set_slave() failed: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -2;
	}	
		
	if ( optind >= argc ) {
		//
		int i;
		int n;
		reg_t *reg;
		uint16_t data[2];

		fprintf(stdout, "[");

		n = 0;
		reg = jys_9y4_registers;
		for(i = 0; i < (sizeof(jys_9y4_registers) / sizeof(reg_t)); i++, reg++ ) {
			if ( !get_all && (reg->min == 0) )
				continue;

 			if ( reg->addr >= 40001 ) {
				if ( modbus_read_registers(ctx, reg->addr - 40001, reg->len, data) == -1 ) {
					fprintf(stderr, "Slave Read failed: %s\n", modbus_strerror(errno));
					break;
				}

				if ( n != 0 ) {
					fprintf(stdout, ",\n");
				}
				fprintf(stdout, "{ \"addr\": %d, \"name\": \"%s\" , \"descr\": \"%s\", \"value\": %s }",
					reg->addr, reg->name, reg->descr, format_value(reg->type, data));
				n++;
			}
		}
		
		fprintf(stdout, "]\n");
	}
	else {
		uint16_t reg_addr;
		uint16_t n = 1;
		static uint16_t data[42];

		reg_addr = atoi(argv[optind++]);
		if ( optind < argc ) {
			n = atoi(argv[optind++]);
			n = n > 42 ? 42 : n;
		}

		if ( reg_addr >= 40001 ) {
			int i;

			if ( modbus_read_registers(ctx, reg_addr - 40001, n, data) == -1 ) {
				fprintf(stderr, "Slave Read failed: %s\n", modbus_strerror(errno));
				modbus_free(ctx);
				return -2;
			}

			if ( n != 1 ) {
				fprintf(stdout, "[");
			}

			for ( i = 0; i < n; i++ ) {
				if ( i != 0 ) {
					fprintf(stdout, ",\n");
				}
				fprintf(stdout, "{ \"addr\": %u, \"value\": %u }", reg_addr + i, data[i]);
			}
			
			if ( n != 1 ) {
				fprintf(stdout, "]");
			}
			fprintf(stdout, "\n");
		} 
	}

	modbus_close(ctx);
	modbus_free(ctx);

	return 0;
}
