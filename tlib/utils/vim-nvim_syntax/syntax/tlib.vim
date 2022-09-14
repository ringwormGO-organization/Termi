" Cmbal syntax file for Vim/Neovim
" Language: tlib

" save current cpo configuration
:if exists("b:current_syntax")
:  finish
:endif

:let s:cpo_save = &cpo
:set cpo&vim

" keywords
:syntax keyword cmbalKeyword IF THEN ENDIF if then endif 

" builtin functions
:syntax keyword cmbaFunctions PRINT INPUT print input

:highlight link cmbalKeyword Keyword
:highlight link cmbaFunctions Function

:let b:current_syntax = "cmbal"

" reset the previous cpo configuration
:let &cpo = s:cpo_save
:unlet! s:cpo_save
