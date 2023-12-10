let loaded_netrwPlugin = 1
lua require("Key-map")
lua require("Lazy")
lua require("Plugins-config/treesitter")
lua require("Plugins-config/setup")
lua require("Plugins-config/cmp")
lua --require("Plugins-config/trouble")
lua require("Plugins-config/dashboard")
lua require("Plugins-config/lsp-config")

lua require("Plugins-config/util")
lua require("Plugins-config/c")
lua --require("Plugins-config/trouble")
colorscheme gruvbox

autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

set su
set number
set relativenumber
set modifiable
lua --禁止创建备份文件
lua vim.o.backup = false
lua vim.o.writebackup = false
lua vim.o.swapfile = false

