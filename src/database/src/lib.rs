use std::ffi::c_int;

#[unsafe(no_mangle)]
extern "C" fn hello(a: c_int) {
    println!("Hello {}!", a);
}
