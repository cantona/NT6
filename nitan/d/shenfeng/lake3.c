inherit ROOM;

void create()
{
        set("short", "銀瀑");
        set("long", @LONG
溪水轉彎繞過一塊高地，忽然眼前一片銀瀑，水聲轟轟不
絕，匹練有如自天而降，飛珠濺玉，頓成奇觀。在這荒涼的大
漠之中突然見此美景，不覺身神俱爽，好奇心起，想看看瀑布
之上更有甚麼景色。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"lake4",
                  "south" : __DIR__"lake2",
        ]));

        setup();
        replace_program(ROOM);
}