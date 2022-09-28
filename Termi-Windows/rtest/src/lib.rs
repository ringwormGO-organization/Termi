#![allow(non_snake_case)]

use libloading::{Library, Symbol};

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

fn AddLog(fmt: &CStr) {
    unsafe {
        let lib = Library::new("Termi-GUI.dll").unwrap();
        let foo = lib
            .get::<Symbol<extern "C" fn(*const c_char)>>(b"AddLog")
            .unwrap();

        foo(fmt.as_ptr());
    }
}

fn GetArgument(arg: *const c_char) -> CString {
    let arg_buf = unsafe { CStr::from_ptr(arg) };
    let arg_str = arg_buf.to_str().unwrap();
    let argument = CString::new(arg_str).expect("CString::new failed!");

    return argument;
}

#[no_mangle]
pub extern "C" fn rust_function(arg: *const c_char) {
    let mut i: u32 = 0;

    while i < 3000 {
        let num_str = CString::new("y").expect("CString::new failed!");
        AddLog(&num_str);
        i += 1;
    }

    let new_line = CString::new("\n").expect("CString::new failed!");
    let text = CString::new("This function is called from Rust programming langauge")
        .expect("CString::new failed!");
    

    AddLog(&new_line);
    AddLog(&text);
    AddLog(&GetArgument(arg));
}
