// guanjinglou.c 觀景樓
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "觀景樓");
        set("long", @LONG
這裡是一座兩層的小樓，是建築在莊園邊緣用來登高憑攔看
風景的。你輕輕靠在欄桿上，竟朽的吱吱做響。看來已經很久沒
有人有這個雅興來這裡看風景了。窗戶(window)上的窗紙已經破
了不少，風一吹嘩嘩的響。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "north" : __DIR__"houhuayuan",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
        "window": "窗外是黃沙滿天，往遠處看，什麼都看不清楚。\n"
        ]) );

        set("coor/x", -12230);
	set("coor/y", 750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}