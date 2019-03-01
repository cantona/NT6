#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", HIB "【寂滅司】" NOR);
        set("long", HIB @LONG

                    寂         滅         司

    寂滅司內寒氣森森，青石舖設的地面滿是灰塵。堂周青布圍幔，圍幔
上用金銀絲線繡著些奇怪的圖案，正堂上一張青石桌案 (table)，桌案上
布滿了蛛網，看樣子很久沒打掃過了。

LONG NOR );

        set("item_desc", ([
                "table" : WHT "一個青石制成的桌案，上面有幾許"
                          "裂縫，看樣子已擱在這裡很久了。\n" NOR,
        ]));

        set("exits", ([
                "east"  : __DIR__"lunhuisi_road1",
                "west"  : __DIR__"yanluodian",
                "north" : __DIR__"heisenlin/entry",
        ]));

        set("no_magic", 1);
        setup();
}
