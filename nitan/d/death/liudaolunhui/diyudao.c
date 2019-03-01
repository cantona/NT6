#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "\n\n                地        獄        道" NOR);
        set("long", HIR "\n"
"極寒極冷，受盡各種折磨，毫無喜樂之所。若與人間比較，第\n"
"一獄以人間三千七百五十年為一年，在此須受困一萬年，相當\n"
"于人間一百三十五億年。而到了第十八地獄，便以億億億年為\n"
"單位，如此長期的受刑可謂是名符其實的萬劫不復。\n\n" NOR);

        set("objects", ([
                __DIR__"npc/diyudaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
