#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h> 
#define MAX_PAYLOAD 127
#define MAX_VALUE_VAR 255
#define STATUS_CODE_ASK 0x00
#define STATUS_CODE_ANSWER 0x01
#define VAR_LIST_CODE_ASK 0x02
#define VAR_LIST_CODE_ANSWER 0x03
#define VAR_READ_CODE_ASK 0x10
#define VAR_READ_CODE_ANSWER 0x11
#define VAR_WRITE_CODE_ASK 0x20
#define PING_CODE 0xD6
#define OK_CODE 0xE0
#define BAD_MESSAGE_CODE 0xE1
#define OP_NOT_SUPPORTED_CODE 0xE2
#define INVALID_ID_CODE 0xE3
#define INVALID_VALUE_CODE 0xE4
#define INVALID_PAYLOAD_CODE 0xE5
#define NO_MEMORY_CODE 0xE7
#define INTERNAL_ERROR_CODE 0xE8
#define READ_ONLY_COMMAND 0xE6

typedef struct vheader{
	unsigned char id;
	unsigned char type; //1 bit?
	unsigned char size;
}variable_header;

typedef struct cheader{
	unsigned char command;
	unsigned char size;
	unsigned char p[MAX_PAYLOAD];
}__attribute__((packed))  command_header;


unsigned char calculate_size(unsigned char size);
int status_command_ask(command_header *status);
int status_command_answer(command_header *status);
int var_list_command_ask(command_header *varlist);
int var_list_command_answer(command_header *varlist,int size);
int var_read_command_ask(command_header *varread);
int var_read_command_answer(command_header *varread, int size);
int var_write_command_ask(command_header *varwrite,int size);
int ping_command(command_header *ping, int size);
static int error_commands(command_header *error,int code);
int ok_command(command_header *error);
int bad_message_command(command_header *error);
int op_not_supported_command(command_header *error);
int invalid_id_command(command_header *error);
int invalid_value_command(command_header *error);
int invalid_payload_command(command_header *error);
int read_only_command(command_header *error);
int no_memory_command(command_header *error);
int internal_error_command(command_header *error);
void free_payload(command_header *error);

