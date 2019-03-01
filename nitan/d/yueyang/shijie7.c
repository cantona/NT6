// Room: /d/yueyang/shijie7.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "城門石階");
        set("long", @LONG
這是岳陽城門外的石階，下邊就是洞庭湖的碼頭。石階由于來往漁
民甚多，不但潮濕，而且沾染了濃重的魚腥味。石階上坐著一些乞丐，
手裡拿著竹杖或破碗，似在乞討。有時也見一些身著百納衣卻衣冠鮮亮
的人，匆忙掩鼻而過。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "south"    : __DIR__"dianjiangtai",
                "eastup"   : __DIR__"ximen",
                "westdown" : __DIR__"matou1",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 3,
        ]));
	set("coor/x", -6230);
	set("coor/y", -3010);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}