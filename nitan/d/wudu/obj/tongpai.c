#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_read", "see");
}

void create()
{
        set_name( YEL "銅牌" NOR, ({"tong pai"}));

        set("unit", "面");
        set("long", YEL "這是一面四四方方的銅牌,上面刻着:“千蛛萬毒”四個大字。\n" NOR
                    "銅牌背面好像雕着一些細細的花紋，需要仔細看(see)才能勉強看清楚。\n" );
        set("value", 50);
        set_weight(200);
        
        setup();
}

int do_read(string arg)
{
        return notify_fail(YEL "                      \n"
"                                   ^                 \n"
"                                @@^ ^     ^          \n"
"                                 ^ ^ ^   ^ ^@@@      \n"
"                              @@@@^ ^ ^ ^ ^ ^        \n"
"                               ^ ^ ^ ^ ^ ^ ^ ^       \n"
"                              ^ ^ ^ ^ ^ ^ ^ ^ ^      \n"
"                             ^ ^ ^ ^O^ ^O^ ^O^ ^     \n"
"                            ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^    \n"
"                           ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^   \n"
"                          ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^  \n" NOR );
}

