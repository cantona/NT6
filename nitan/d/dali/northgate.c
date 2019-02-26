//Room: /d/dali/northgate.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","北門");
        set("long", @LONG
陽苜咩城，或簡稱苜咩城，是大理國的都城。自南詔於初創，歷
經陳氏『長大和國』、趙氏『大天興國』、楊氏『大義寧國』諸代而
至當今的段氏的『大理國』，均以此城為都。此處乃是北城門，以梅
溪為護河，城牆建在溪南，由石塊和土壘成，高二丈五，厚達二丈，
門上有重樓，駐有了哨。青石官道從城裏直向北延伸，另有一條黃土
大路向西通去。
LONG );
        set("objects", ([
           "/d/dali/npc/bing": 4,
           "/d/dali/npc/jiang": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "south"     : "/d/dali/paifang",
            "north"     : "/d/dali/dalinorth",
            "east"      : "/d/dali/chahuashan1",
            "west"      : "/d/dali/shanlu3",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}