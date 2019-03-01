// yuefen.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "岳墳");
        set("long", @LONG
墓道兩旁有石虎，石羊，石馬和三對翁仲。正中古柏交柯，便是岳飛的
墳墓。墓碑刻著“宋岳鄂王墓”。岳王墓的左面，便是岳飛之子岳雲的墓，
墓碑上刻著“宋繼忠侯岳雲之墓”。在岳墳前面兩邊四個鐵像(statue)。東
首牆上有四個大字(word)。
LONG);
        set("exits", ([
            "south"     : __DIR__"yuelang",
        ]));
        set("item_desc" , ([
            "statue" :
"北邊兩個是秦檜和他的妻子王氏；南邊兩個是同謀殺害岳飛的姦臣，
張俊和萬俟屑。四個鐵像都反剪著手，向岳墓跪著。\n",
            "word"   :
"牆上有“精忠報國”四個大字。這是岳母當年訓子時在岳飛背上刻的字。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -1990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}