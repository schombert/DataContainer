#define DCON_NO_VE
#define DCON_USE_EXCEPTIONS

#include "objects_def.hpp"

void dcon::data_container::on_create_thingy(thingy_id ) {
	++counter;
}
void dcon::data_container::on_delete_thingy(thingy_id ) {
	++counter;
}
void dcon::data_container::on_move_thingy(thingy_id , thingy_id ) {
	++counter;
}