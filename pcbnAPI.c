#include "pcbnAPI.h"

int build_variable(int ID, int type, int size, int value);

unsigned char calculate_size(unsigned char size){
	if (size || 128)
		return 128*(size+1)+2;
	return (unsigned char)size;
}

int status_command_ask(command_header *status){
	status->command = STATUS_CODE_ASK;
	status->size = 0x00;
	status->p = NULL;
	return (sizeof(status->command)+sizeof(status->size));
}

int status_command_answer(command_header *status){
	status->command = STATUS_CODE_ANSWER;
	status->size = 0x00;
	status->p = NULL;
	return (sizeof(status->command)+sizeof(status->size));
}

int var_list_command_ask(command_header *varlist){
	varlist->command = VAR_LIST_CODE_ASK;
	varlist->size = 0x00;
	varlist->p = NULL;
	return (sizeof(varlist->command)+sizeof(varlist->size));
}

int var_list_command_answer(command_header *varlist,int size){
	varlist->command = VAR_LIST_CODE_ANSWER;
	varlist->size = size;
	varlist->p = (unsigned char*)malloc(sizeof(unsigned char)*size);
	return (sizeof(varlist->command)+sizeof(varlist->size)+size);
}

int var_read_command_ask(command_header *varread){
	varread->command = VAR_READ_CODE_ASK;
	varread->size = 0x01;
	varread->p = (unsigned char*)malloc(sizeof(unsigned char)*varread->size);
	return (sizeof(varread->command)+sizeof(varread->size)+1);
}

int var_read_command_answer(command_header *varread, int size){
	varread->command = VAR_READ_CODE_ANSWER;	
	varread->size = size;
	varread->p = (unsigned char*)malloc(sizeof(unsigned char)*varread->size);
	return (sizeof(varread->command)+sizeof(varread->size)+size);
}

int var_write_command_ask(command_header *varwrite,int size){
	varwrite->command = VAR_WRITE_CODE_ASK;
	varwrite->size = 1 + size;
	varwrite->p = (unsigned char*)malloc(sizeof(unsigned char)*varwrite->size);
	return (sizeof(varwrite->command)+sizeof(varwrite->size)+size+1);
}

int ping_command(command_header *ping, int size){
	ping->command = PING_CODE;
	ping->size = 8 + size;
	ping->p = (unsigned char*)malloc(sizeof(unsigned char)*ping->size);
	return (sizeof(ping->command)+sizeof(ping->size)+size+8);
}

static int error_commands(command_header *error,int code){
	error->command = code;
	error->size = 0x0;
	error->p = NULL;
	return 2;
}

int ok_command(command_header *error){
	return error_commands(error,OK_CODE);
}
int bad_message_command(command_header *error){
	return error_commands(error,BAD_MESSAGE_CODE);
}

int op_not_supported_command(command_header *error){
	return error_commands(error,OP_NOT_SUPPORTED_CODE);
}
	
int invalid_id_command(command_header *error){
	return error_commands(error,INVALID_ID_CODE);
}

int invalid_value_command(command_header *error){
	return error_commands(error,INVALID_VALUE_CODE);
}

int invalid_payload_command(command_header *error){
	return error_commands(error,INVALID_PAYLOAD_CODE);
}

int read_only_command(command_header *error){
	return error_commands(error,READ_ONLY_COMMAND);
} 

int no_memory_command(command_header *error){
	return error_commands(error,NO_MEMORY_CODE);
}

int internal_error_command(command_header *error){
	return error_commands(error,INTERNAL_ERROR_CODE);
}
void free_payload(command_header *error){
	if (error->p != NULL)
		free(error->p);
	return;
}
