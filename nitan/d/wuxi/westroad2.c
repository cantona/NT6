// Room: /d/wuxi/westroad2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "西新街");
        set("long", @LONG
西新街上的人雖然多得不得了，街面卻還乾淨、整潔。人來人往，
吆喝聲、叫賣聲匯成一片。你看來川流不息的人羣，心裏異常興奮和高
興，街邊的小販吆喝着小籠饅頭和雞湯餛飩，令你食慾大開。南邊的二
泉茶館原本開在惠山下的真正的二泉旁邊，後來為了生意還是搬到這條
街上來了，可每天都是派人專程去二泉用水車拉來泉水沏茶的。路北邊
是這條街上生意最好的客棧，進出的都是來自天南地北的人。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"kedian",
                "south" : __DIR__"chaguan",
                "west"  : __DIR__"westgate",
                "east"  : __DIR__"westroad1",
        ]));
        set("objects", ([
                __DIR__"npc/wulai" : 1,
        ]));
        set("coor/x", 1020);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}