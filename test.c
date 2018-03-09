#include <stdio.h>
#include <vpi_user.h>
#include "usw_vpi.h"

static int hello_compiletf(char*user_data)
{
	return 0;
}

static int test2_cb(struct t_cb_data *cbp)
{
	printf("Hello from %s\n", __func__);
	if (cbp->user_data) {
		struct usw_cb_data *data = (struct usw_cb_data *)cbp->user_data;
		vpi_remove_cb(data->handle);
	}
	return 0;
}

static int hello_calltf(char*user_data)
{
	vpi_printf("Hello, World!\n");
	for (int i=1;i<10;i++) {
		printf("Registering %d callback ...\n", i);
		int r = usw_callback_delay(1, test2_cb, NULL);
		if (r) {
			printf("register timed callback failed\n");
		}
	}

	return 0;
}

void usw_vpi_register(void)
{
	s_vpi_systf_data tf_data;

	tf_data.type      = vpiSysTask;
	tf_data.tfname    = "$usw_vpi";
	tf_data.calltf    = hello_calltf;
	tf_data.compiletf = hello_compiletf;
	tf_data.sizetf    = 0;
	tf_data.user_data = 0;
	vpi_register_systf(&tf_data);
	USW_CHECK_VPI();
}

void (*vlog_startup_routines[])(void) = {
	usw_vpi_register,
	0,
};
