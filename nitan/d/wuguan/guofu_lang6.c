inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，往北通向休息室，南面是物品房，這裏靜悄
悄的，人們走路都也是小心翼翼的。生怕吵着北面休息室裏正
在休息的人。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "north" : __DIR__"guofu_woshi1",
               "south" : __DIR__"guofu_wupinfang",
        ]));
        setup();
        replace_program(ROOM);
}