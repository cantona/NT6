//Room: /d/dali/yanchi2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池堤岸");
        set("long", @LONG
滇池風景怡人，沿堤岸漫步，遵堤行湖中，堤南北皆碧水。蓋其
碧波即草海之餘，南連於滇池，北抵黃土坡，西瀕與赤鼻山之簏。東
行湖中，遙顧四周山色，掩映重波間，青蒲偃水，高柳瀠堤，天然絕
勝。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "westdown" : "/d/dali/yanchi1",
            "east"     : "/d/dali/yanchi3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19090);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}