#![allow(non_snake_case)]

use libloading::{Library, Symbol};

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

#[cfg(target_os = "windows")]
const GUI_PATH: &str = "Termi-GUI.dll";

#[cfg(any(target_os="macos", target_os = "linux", target_os = "freebsd", 
            target_os = "openbsd", target_os = "netbsd"))]
const GUI_PATH: &str = "libTermi-GUI.so";

/// `printf()` for Termi's console
fn AddLog(fmt: &CStr) {
    unsafe {
        let lib = Library::new(GUI_PATH).unwrap();
        let foo = lib
            .get::<Symbol<extern "C" fn(*const c_char)>>(b"AddLog")
            .unwrap();

        foo(fmt.as_ptr());
    }
}

/// Separate string into arguments intended for this Rust program
/// 
/// Returns vector of `CString`
fn GetArguments(arg: *const c_char) -> Vec<CString> {
    let mut vec = Vec::new();

    let arg_buf = unsafe { CStr::from_ptr(arg) };
    let arg_str = arg_buf.to_str().unwrap();

    for word in arg_str.split(' ') {
        let c_string = CString::new(word).expect("CString::new failed!");
        vec.push(c_string);
    }

    return vec;
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
    let text = CString::new("This function is called from Rust programming language")
        .expect("CString::new failed!");
    

    AddLog(&new_line);
    AddLog(&text);

    let arguments_list_line = CString::new("Arguments:").expect("CString::new failed!");
    AddLog(&arguments_list_line);

    for argument in GetArguments(arg) {
        AddLog(&argument);
    }
}
