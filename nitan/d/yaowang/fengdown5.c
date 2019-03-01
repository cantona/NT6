inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
這裡是山谷的谷底，靜悄悄地沒有一點聲響。漆黑的土地上
散落著奇形怪狀的小山石，有些石頭還很尖利，人走在上面東倒
西歪的。北面是一小片低矮的灌木叢。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"fengd1",
  "south" : __DIR__"fengdown4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
