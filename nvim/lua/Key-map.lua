vim.g.mapleader = " "
vim.g.maplocalleader = " "
local map = vim.api.nvim_set_keymap
local opt = {noremap = true, silent = true }
map("n", "<Leader>nt", ":Neotree<Leader>toggle<CR>", opt)
map("n", "<Leader>tm", ":ToggleTerm<CR>", opt)
map( "t", "<ESC>", "<C-\\><C-n>",opt)