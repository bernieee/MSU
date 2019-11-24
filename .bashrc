# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
histcontrol=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see histsize and histfilesize in bash(1)
histsize=1000
histfilesize=2000

# check the window size after each command and, if necessary,
# update the values of lines and columns.
shopt -s checkwinsize

# if set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(shell=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$term" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# we have color support; assume it's compliant with ecma-48
	# (iso/iec-6429). (lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    ps1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    ps1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# if this is an xterm set the title to user@host:dir
case "$term" in
xterm*|rxvt*)
    ps1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$ps1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored gcc warnings and errors
#export gcc_colors='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
alias ll='ls -al --g'
alias la='ls -a'
alias l='ls -l --g'
# alias l="ls -l -h -g -f -x"
# add an "alert" alias for long running commands.  use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# alias definitions.
# you may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# see /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# >>> conda initialize >>>
# !! contents within this block are managed by 'conda init' !!
__conda_setup="$('/home/bernie/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/home/bernie/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/home/bernie/anaconda3/etc/profile.d/conda.sh"
    else
        export path="/home/bernie/anaconda3/bin:$path"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<







# added by Seryozha

bind 'set completion-ignore-case on'

bind '"\e[A": history-search-backward'
bind '"\e[B": history-search-forward'
export PS1="\[\033[32;1m\]\u@\h\[\033[m\]:\[\033[34;1m\]\w\[\033[m\]$ "
#export PS1="\[\033[36m\]\u\[\033[m\]@\[\033[32m\]\h:\[\033[33;1m\]\w\[\033[m\]\$ "

export CLICOLOR=1
export LSCOLORS=ExGxBxDxCxegedabagacad


# >>> remember aliases >>>

alias cd...="cd ../.."
alias cd..="cd .."
alias cd-="cd -"
alias clr="clear"
alias v="vim"
alias gccc="gcc -g -O2 -Wall -lm -fsanitize=undefined"

function f() {
    l | grep -i "$1"; ls -f -a | grep -i -c "$1"
}

function gcca() {
    gccc "$1"; ./a.out
}

alias aout="./a.out"
alias hlp="less ~/.SERYOZHA.md"
# <<< remember aliases <<<

eval $(/home/linuxbrew/.linuxbrew/bin/brew shellenv)
