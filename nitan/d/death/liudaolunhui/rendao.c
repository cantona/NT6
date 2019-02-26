#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + WHT "\n\n                人        間        道" NOR);
        set("long", WHT "\n"
"彷彿踏進了嘈雜的鬧市，又如闖進了民家大院。歡笑聲、哭泣\n"
"聲、怒罵聲相互交雜。喜怒哀樂、恩怨情仇，世間百態盡集於\n"
"此。嚐盡人間種種酸甜苦辣，悲歡離合。於痛苦中誕生，又於\n"
"痛苦中消逝。憐我世人，憂患實多。憐我世人，憂患實多。\n\n" NOR);
        
        set("objects", ([
                __DIR__"npc/rendaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
