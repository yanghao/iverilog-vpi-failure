#include "usw_vpi.h"

const char *reason_to_string(int reason)
{
	switch (reason) {
		CASE_STR(cbValueChange);
		CASE_STR(cbAtStartOfSimTime);
		CASE_STR(cbReadWriteSynch);
		CASE_STR(cbReadOnlySynch);
		CASE_STR(cbNextSimTime);
		CASE_STR(cbAfterDelay);
		CASE_STR(cbStartOfSimulation);
		CASE_STR(cbEndOfSimulation);

		default: return "unknown";
	}
}

void usw_sim_time(uint32_t *high, uint32_t *low)
{
	s_vpi_time vpi_time_s;
	vpi_time_s.type = vpiSimTime;       //vpiSimTime;
	vpi_get_time(NULL, &vpi_time_s);
	USW_CHECK_VPI();
	*high = vpi_time_s.high;
	*low = vpi_time_s.low;
}

/* general callback, relative time assumed */
int usw_callback(uint32_t reason, vpiHandle handle, uint64_t time,
		USW_TYPE_CALLBACK callback, struct usw_cb_data *user_data)
{
	switch (reason) {
		case cbAtStartOfSimTime:
		case cbAfterDelay:
		case cbReadWriteSynch:
		case cbNextSimTime:
		case cbValueChange:
			break;
		default:
			printf("reason (%d) is not supported: %s\n", reason,
					reason_to_string(reason));
			return -1;
	}
	//s_vpi_time vpi_time;
	s_cb_data cb_data;
	s_vpi_time vpi_time;

	vpi_time.high = (uint32_t)(time>>32);
	vpi_time.low  = (uint32_t)(time);
	vpi_time.type = vpiSimTime;

	cb_data.reason = reason;
	cb_data.cb_rtn = callback;
	cb_data.obj = handle;
	cb_data.time = &vpi_time;
	cb_data.value = NULL;
	cb_data.index = 0;
	cb_data.user_data = (void *)user_data;

	vpiHandle new_hdl = vpi_register_cb(&cb_data);
	if (user_data) {
		user_data->handle = new_hdl;
	}
	if (!new_hdl) {
		printf("VPI: Unable to register a callback handle for VPI type %s(%d)\n",
				reason_to_string(cb_data.reason), cb_data.reason);
		USW_CHECK_VPI();
		return -1;

	}
	return 0;
}

/* relative time call back, before events */
int usw_callback_delay(uint64_t time, USW_TYPE_CALLBACK callback,
		struct usw_cb_data *user_data)
{
	//return usw_callback(cbAfterDelay, NULL, time, callback, user_data);
	return usw_callback(cbAtStartOfSimTime, NULL, time, callback, user_data);
}
