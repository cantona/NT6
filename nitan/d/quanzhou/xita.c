// Room: /d/quanzhou/xita.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "西塔");
        set("long", @LONG
西塔又名仁壽塔，它與東塔除局部略有區別外，建築規則基本相同，
恰似一對攣生姊妹。西塔須彌座束腰部分則雕刻著各種花、鳥、蟲、獸
和裝飾圖案，也都線條清晰，形態逼真，給人一種欣悅、舒暢的美感。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"yuetai",
        ]));
	set("coor/x", -930);
	set("coor/y", -7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}