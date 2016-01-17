
#####让vim显示行尾的空格:
在vimrc文件添加如下两行
```
highlight WhitespaceEOL ctermbg=red guibg=red 
match WhitespaceEOL /\s\+$/
```


#####设置字体   
In gvim, you can change the font using the Edit menu, Select Font. An alternative is to enter the command:
`    :set guifont=* `
Once you have a font you like, you want to make it the default in the future. Do
`    :set guifont?`
and Vim will display something like
`    guifont=Lucida_Console:h11 `
Make a note of this string. Now put a line in your vimrc to set guifont to this value, like this:
```
    if has('gui_running')
      set guifont=Lucida_Console:h11
    endif
```
Note: If there is a space in the text printed, such as
`    guifont=Monospace 10`
it will be necessary to escape the space
`    set guifont=Monospace\ 10`


#####vim 的wiki  
http://vim.wikia.com/wiki/Vim_Tips_Wiki



#####vimrc
set nu
set ts=4 sw=4 st=4
set expandtab
set autoindent
set smartindent
set guifont=Monospace\ 12
colorscheme evening
let Tlist_Use_Right_Window=1
highlight WhitespaceEOL ctermbg=red guibg=red
match WhitespaceEOL /\s\+$/


