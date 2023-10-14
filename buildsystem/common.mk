
# $1 prefix
# $2 string
# $3 suffix

define surround
$(addprefix $1,$(addsuffix $3,$2))
endef

