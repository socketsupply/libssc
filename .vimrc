let g:clang_format#auto_format=1

au BufNewFile,BufRead *.h set filetype=c
au BufNewFile,BufRead *.h set syntax=c

set tabstop=2
set shiftwidth=2
set softtabstop=2

set smarttab
set expandtab
set autoindent
set smartindent
set nocompatible

fun! CFormatSettings()
  setlocal equalprg=clang-format
endfun

autocmd FileType c,h call CFormatSettings()

fun s:c()
  " Comments
  syn keyword   Todo             TODO FIXME XXX TBD contained
  syn region    Comment          start=/\/\// end=/$/ contains=Todo,@Spell
  syn region    Comment          start=/\/\*/ end=/\*\// contains=Todo,@Spell

  hi def link   Todo             Todo
  hi def link   Comment          Comment

  " Natspec
  syn match     NatspecTag       /@see\>/ contained
  syn match     NatspecTag       /@dev\>/ contained
  syn match     NatspecTag       /@title\>/ contained
  syn match     NatspecTag       /@author\>/ contained
  syn match     NatspecTag       /@notice\>/ contained
  syn match     NatspecTag       /@param\>/ contained
  syn match     NatspecTag       /@prop\>/ contained
  syn match     NatspecTag       /@return\>/ contained
  syn match     NatspecTag       /@throws\>/ contained
  syn match     NatspecTag       /@returns\>/ contained
  syn match     NatspecTag       /@example\>/ contained
  syn match     NatspecParam     /\(@param\s*\)\@<=\<[a-zA-Z_][0-9a-zA-Z_]*/
  syn region    NatspecBlock     start=/\/\/\// end=/$/ contains=Todo,NatspecTag,NatspecParam,@Spell
  syn region    NatspecBlock     start=/\/\*\{2}/ end=/\*\// contains=Todo,NatspecTag,NatspecParam,@Spell

  hi def link   NatspecTag       SpecialComment
  hi def link   NatspecBlock     Comment
  hi def link   NatspecParam     Define
endfun

augroup ft_c
  autocmd!
  autocmd Syntax c call s:c()
augroup end
