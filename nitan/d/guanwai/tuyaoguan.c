// /guanwai/tuyaoguan.c

inherit ROOM;

void create()
{
        set("short", "土窯館");
        set("long", @LONG
一邁進這間小房，一股脂粉混合著大蒜的味道撲鼻而來，差點把你嗆了
一個跟頭。屋內點著很多蠟燭和燈籠，把四壁照得通紅。很多穿著破爛的漢
子，一手摟著姑娘，一個握著酒壺，正在高談闊論。一個肥胖的老鴉一遍招
待著客人，一遍大聲催促的這裡的伴當和姑娘們。
LONG );
        set("exits", ([
                "north" : __DIR__"dongcheng",
        ]));
        set("objects", ([
                __DIR__"npc/jiaowenqi" : 1,
        ]));
//        set("no_clean_up", 0);
//        set("outdoors", "guanwai");
        set("coor/x", 4000);
	set("coor/y", 9230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
