#ifndef USW_VPI_H
#define USW_VPI_H

#include <string.h>
#include <sv_vpi_user.h>

#define CASE_STR(_X) \
    case _X: return #_X

#define USW_VPI_CHECKING

#define USW_CHECK_VPI()

struct usw_cb_data {
	vpiHandle handle;
};

typedef int (*USW_TYPE_CALLBACK)(p_cb_data cbp);

const char * reason_to_string(int reason);

/* Sim related */
void usw_sim_end(void);
void usw_sim_time(uint32_t *high, uint32_t *low);
long usw_sim_precision(void);

/* Hierachy related */
vpiHandle usw_root_handle(const char *name);
void usw_scan(vpiHandle root, int type, int level);

/* callback related */
int usw_callback(uint32_t reason, vpiHandle handle, uint64_t time,
		USW_TYPE_CALLBACK callback, struct usw_cb_data *user_data);
int usw_callback_time(uint64_t time, USW_TYPE_CALLBACK, struct usw_cb_data *user_data);
int usw_callback_delay(uint64_t time, USW_TYPE_CALLBACK, struct usw_cb_data *user_data);
int usw_callback_sync(uint64_t time, USW_TYPE_CALLBACK, struct usw_cb_data *user_data);
int usw_callback_next(USW_TYPE_CALLBACK, struct usw_cb_data *user_data);

#endif /* USW_VPI_H */
