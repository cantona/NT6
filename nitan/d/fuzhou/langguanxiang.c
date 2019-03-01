// Room: /d/fuzhou/langguanxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "郎官巷");
        set("long", @LONG
宋劉濤曾居于此，子孫數世皆為郎官，故名郎官巷。宋代名詩人陳
烈，清代名人嚴復的故居也坐落巷內。郎官巷口立有牌坊，坊柱上有副
對聯：“譯著輝煌，今日猶傳嚴復宅；門庭鼎盛，後人遠溯劉濤居。”
LONG );

        set("exits", ([
                "west"    : __DIR__"nanhoujie2",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}