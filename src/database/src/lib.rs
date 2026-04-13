#![allow(dead_code, mutable_transmutes, non_camel_case_types, non_snake_case, non_upper_case_globals, unused_assignments, unused_mut)]

use std::ffi::c_char;
use std::ffi::c_int;
use std::ffi::c_uint;
use std::ffi::CStr;

use std::fs::File;
use std::io::prelude::*;

const DATABASE_PATH: &str = ".database";

const UUID_STR_LEN: usize = 37;
const MAX_NAME_LENGTH: usize = 32;

#[derive(Copy, Clone)]
#[repr(C)]
pub struct user_data_t {
    pub uuid: [c_char; UUID_STR_LEN],
    pub username: [c_char; MAX_NAME_LENGTH + 1],
    pub status: c_int,
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct users_t {
    pub users: *const *const user_data_t,
    pub amount: c_uint,
    pub size: c_uint,
}

// impl users_t {
//     fn user_data(&self) -> impl Iterator<Item = *mut user_data_t> {
//         unsafe {
//             std::slice::from_raw_parts(
//                 self.users,
//                 self.amount as usize,
//             )
//             .into_iter()
//         }
//     }
// }

#[unsafe(no_mangle)]
fn save_user(user_data: *const user_data_t) {

}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn save_users(mut users: *mut users_t) {
    let path = String::from(DATABASE_PATH) + "/users.neige";

    let mut output_file = File::create(path);
    // if output_file.is_err() {
    //     return;
    // }

    for user_data in unsafe {
        std::slice::from_raw_parts(
            (*users).users,
            (*users).amount as usize,
        ).into_iter()
    } {
        save_user(*user_data);
    }
    // write!(output_file.unwrap(), "caca");
}
