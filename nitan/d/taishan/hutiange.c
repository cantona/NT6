// Room: /d/taishan/hutiange.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "壺天閣");
        set("long", @LONG
壺天閣名取自道家以壺天為仙境之意。明代稱升仙閣，清乾隆皇帝
登岱時拓建改今名。閣為跨道門樓式建築，清嘉慶年間崔映辰題聯：“
壺天日月開靈境，盤路風雲入翠微。”廷璐又聯：“登此山一半已是壺
天，造極頂千重尚多福地。”門洞有雙柏自牆中橫生，盤旋而上，堪稱
奇景。
LONG );
        set("exits", ([
                "westup"    : __DIR__"huima",
                "southdown" : __DIR__"sihuaishu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 180);
	set("coor/z", 80);
	setup();
        replace_program(ROOM);
}