// Room: /qingcheng/huyingting.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "呼應亭");
        set("long", @LONG
呼應亭高居彭祖峰頂，是青城最高處。登臨長嘯，余音回盪，
眾山皆應。看雪嶺光騰，紅吞滄海，錦江春漲，綠到瀛洲。夏日夜
分，有聖燈浮雲，傳說是神仙朝賀張天師所點仙燈，看來讓人感嘆
不已。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "eastdown" : __DIR__"shangqing",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -880);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}