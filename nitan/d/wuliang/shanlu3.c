// Room: /wuliang/shanlu3.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路漸漸崎嶇難行，側轉一個彎，蜿蜒向上，更是艱險。你抬頭
望去，卻只見東邊山腰裏冒起一條條的裊裊青煙，共有十餘叢之多，
不知道是甚麼意思。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"shanlu2",
                "eastup"    : __DIR__"shanlu4",
        ]));
        set("coor/x", -71000);
        set("coor/y", -79990);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}