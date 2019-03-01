// /d/xiakedao/shiroom21.c 俠客島 石室21

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
進門便覺精神一振，原來上方有一尺許見方的通風孔，不似其他
石室那般氣悶。一抹陽光從孔中透入，投在對面的石壁(wall)上。隱
隱也能聽見外面的鳥雀嘰嚓飛過，令人片刻間神遊物外。
LONG );
        set("exits", ([
                "south" : __DIR__"shihole6",
        ]));
        set("item_desc", ([
                "wall" : @WALL
牆的正上方刻着「縱死俠骨香」幾個大字。下面繪的是春秋時另一個
慘烈的故事「要離刺慶忌」。那要離身材既矮，且又獨臂，但一股殺
氣直是攝人魂魄。一行注云：韓昌黎詩：想當施手時，巨刃摩天揚。
又注：叱吒則風雲變色。
WALL
        ]));
        set("objects", ([
                __DIR__"master/miejue" : 1,
                __DIR__"master/zhou"   : 1,
        ]));
/*
周芷若説道：徒兒定會緊記與心的。

周芷若一式「閃現雷鳴」，左掌外旋上挑，右指內翻前指，閃點般急點滅絕師太的左臉！
結果被滅絕師太擋開了。

周芷若一式「閃現雷鳴」，左掌外旋上挑，右指內翻前指，閃點般急點滅絕師太的後心！
結果只聽見滅絕師太一聲慘嚎，指力已在滅絕師太的後心對穿而出，鮮血濺得滿地！！
( 滅絕師太受傷不輕，看起來狀況並不太好。 )
周芷若説道：這一句是否指出掌必盡全力，傷敵無慮
*/
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("coor/x", -3090);
        set("coor/y", -25590);
        set("coor/z", 0);
        setup();
}

#include "/d/xiakedao/shiroom.h"