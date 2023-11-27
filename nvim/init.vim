lua require("Key-map")
lua require("Lazy")
lua require("Plugins-config/treesitter")
lua require("Plugins-config/setup")
lua require("Plugins-config/cmp")
colorscheme tokyonight

autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

set su
set number
set relativenumber
