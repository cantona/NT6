// Room: /d/taishan/xiaodongtian.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "小洞天");
        set("long", @LONG
紅門宮東北深澗內，就是小洞天。這裡片石如幾，厚五尺，方圓丈
許。此處一壑曲繞，清溪碧潭，山林澗草，森森蔓蔓，別有洞天。南側
有明代知泰安州事甘應甲題、范廣書“小洞天”。谷底斷崖層疊，橫瀑
飛流，自北而南有柳條、飲馬、石峽三灣。谷側多圓柱形鐵黑色巨石，
橫斷面層層包裹，似枯木年輪，上刻“醉心”。
LONG );
        set("exits", ([
                "southwest" : __DIR__"hongmen",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 80);
	set("coor/y", 90);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}