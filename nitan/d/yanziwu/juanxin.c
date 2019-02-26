// Room: /d/yanziwu/juanxin.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "倦心亭");
        set("long", @LONG
倦心亭正在蔓陀山峯崖下。崖上飛瀑直指蓮韻塘底，風聲雨氣，讓
人渾然忘卻人世間的煩惱。這裏常有傷心人流連抒懷。亭中石桌上刻着
“曾經滄海難為水  除卻巫山不是雲  取次花叢懶回顧  半緣修道半緣
君。”筆致甚為都雅。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"bridge3",
        ]));
        set("coor/x", 1220);
        set("coor/y", -1200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}