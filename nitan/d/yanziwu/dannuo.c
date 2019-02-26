//ROOM: /d/yanziwu/dannuo.c

inherit ROOM;
void create()
{
        set("short", "啖糯廳");
        set("long", @LONG
這是一間雅緻的大廳，廳上擺着幾張紫檀木大桌。桌上銀製餐具
一應俱全，桌邊一溜犁花木椅。每日慕容世家很多人都在此用餐。
LONG );
        set("exits", ([
            "west" : __DIR__"yimen",
            "east" : __DIR__"huayuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}