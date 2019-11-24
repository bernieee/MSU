set nocompatible
filetype off
syntax on

set number
set autoindent
set listchars=tab:▸\ ,trail:·
set list
set mouse=a
set smartindent
set smarttab
set shiftwidth=4
set softtabstop=4
set tabstop=4
set expandtab
set clipboard=unnamed

nnoremap ; :
nnoremap <C-a> ^
nnoremap <C-e> $
nnoremap <C-d> :t. <CR> <CR>
nnoremap <C-c> :%w !pbcopy <CR> <CR>
nnoremap <C-v> :%r !pbpaste <CR> <CR>
nnoremap <C-f> :e# <CR> <CR>

vnoremap ; :
vnoremap <C-a> ^
vnoremap <C-e> $
vnoremap <C-c> :%w !pbcopy <CR> <CR>
vnoremap <C-v> :%r !pbpaste <CR> <CR>
vnoremap <C-f> :e# <CR> <CR>

inoremap <C-a> <Esc> I
inoremap <C-e> <Esc> A
inoremap <C-d> <Esc> :t. <CR> i
