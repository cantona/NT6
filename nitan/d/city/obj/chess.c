// chess.c
#include <ansi.h>
#define che TABLE[table[sROW]][sCOL][2]
#define cc TABLE[table[sROW]][sCOL][3]
#define cc1 TABLE[table[tROW]][tCOL][3]
inherit ITEM;
inherit F_SAVE;

string bche = "";
string rche = "";
string aaa = "";
int aa = 0;
int bb = 0;

mapping TABLE = ([ // table /*庚庖征忠岸岱念怕房拂拈*/
0: ([
        0 :({ "庚",HIR"陬"NOR, 1,1 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "房",HIR"鎮"NOR, 2,1 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "房",HIR"眈"NOR, 3,1 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "房",HIR"帊"NOR, 4,1 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "房",HIR"邟"NOR, 5,1 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "房",HIR"帊"NOR, 4,1 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "房",HIR"眈"NOR, 3,1 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "房",HIR"鎮"NOR, 2,1 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "庖",HIR"陬"NOR, 1,1 }),
        ]),
1: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "ㄞ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
2: ([
        0 :({ "念", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕", "  ", 0,0 }),
        ]),
3: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "ㄞ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
4 : ([
        0 :({ "念", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈",HIR"蘿"NOR, 6,1 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈",HIR"蘿"NOR, 6,1 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕", "  ", 0,0 }),
        ]),
5 : ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "  ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "  ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
6 : ([
        0 :({ "念",HIR"條"NOR, 7,1 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈",HIR"條"NOR, 7,1 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈",HIR"條"NOR, 7,1 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈",HIR"條"NOR, 7,1 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕",HIR"條"NOR, 7,1 }),
        ]),
7 : ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "  ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "  ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
8 : ([
        0 :({ "征", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拂", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拂", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拂", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拂", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拂", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拂", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拂", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "忠", "  ", 0,0 }),
        ]),
9 : ([
        0 : ({ " ‵‵ 奠  碩 ‵‵‵‵ 犖  賜 ‵‵ ", "  ", 0,0 }),
        ]),
10: ([
        0 :({ "庚", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "房", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "房", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "房", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "房", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "房", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "房", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "房", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "庖", "  ", 0,0 }),
        ]),
11: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "  ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "  ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
12 : ([
        0 :({ "念",HIC"逑"NOR, 7,2 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈",HIC"逑"NOR, 7,2 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈",HIC"逑"NOR, 7,2 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈",HIC"逑"NOR, 7,2 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕",HIC"逑"NOR, 7,2 }),
        ]),
13: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "  ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "  ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
14: ([
        0 :({ "念", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈",HIC"貧"NOR, 6,2 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈",HIC"貧"NOR, 6,2 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕", "  ", 0,0 })
]),
15: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "ㄞ", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
16: ([
        0 :({ "念", "  ", 0,0 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拈", "  ", 0,0 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拈", "  ", 0,0 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拈", "  ", 0,0 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拈", "  ", 0,0 }),
        9 :({ "岸", "  ", 0,0 }),
        10:({ "拈", "  ", 0,0 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拈", "  ", 0,0 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拈", "  ", 0,0 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "怕", "  ", 0,0 })
        ]),
18: ([
        0 : ({ "岱", "  ", 0,0 }),
        1 : ({ "  ", "  ", 0,0 }),
        2 : ({ "岱", "  ", 0,0 }),
        3 : ({ "  ", "  ", 0,0 }),
        4 : ({ "岱", "  ", 0,0 }),
        5 : ({ "  ", "  ", 0,0 }),
        6 : ({ "岱", "  ", 0,0 }),
        7 : ({ "ㄞ", "  ", 0,0 }),
        8 : ({ "岱", "  ", 0,0 }),
        9 : ({ "", "  ", 0,0 }),
        10: ({ "岱", "  ", 0,0 }),
        11: ({ "  ", "  ", 0,0 }),
        12: ({ "岱", "  ", 0,0 }),
        13: ({ "  ", "  ", 0,0 }),
        14: ({ "岱", "  ", 0,0 }),
        15: ({ "  ", "  ", 0,0 }),
        16: ({ "岱", "  ", 0,0 })
        ]),
19: ([
        0 :({ "征",HIC""NOR, 1,2 }),
        1 :({ "岸", "  ", 0,0 }),
        2 :({ "拂",HIC"醪"NOR, 2,2 }),
        3 :({ "岸", "  ", 0,0 }),
        4 :({ "拂",HIC"砓"NOR, 3,2 }),
        5 :({ "岸", "  ", 0,0 }),
        6 :({ "拂",HIC"尪"NOR, 4,2 }),
        7 :({ "岸", "  ", 0,0 }),
        8 :({ "拂",HIC""NOR, 5,2 }),
        9 :({ "岸", "  ", 0,0 }),
10:({ "拂",HIC"尪"NOR, 4,2 }),
        11:({ "岸", "  ", 0,0 }),
        12:({ "拂",HIC"砓"NOR, 3,2 }),
        13:({ "岸", "  ", 0,0 }),
        14:({ "拂",HIC"醪"NOR, 2,2 }),
        15:({ "岸", "  ", 0,0 }),
        16:({ "忠",HIC""NOR, 1,2 }),
        ]),

]);

string *table;

string *tossText = ({

        "岫      岫\n"
        "岫  "HIR"♂"NOR"  岫\n"
        "岫      岫\n",

        "岫  ♂  岫\n"
        "岫      岫\n"
        "岫  ♂  岫\n",

        "岫♂    岫\n"
        "岫  ♂  岫\n"
        "岫    ♂岫\n",

        "岫"HIR"♂  ♂"NOR"岫\n"
        "岫      岫\n"
        "岫"HIR"♂  ♂"NOR"岫\n",

        "岫♂  ♂岫\n"
        "岫  ♂  岫\n"
        "岫♂  ♂岫\n",

        "岫♂  ♂岫\n"
        "岫♂  ♂岫\n"
        "岫♂  ♂岫\n",

        "底岩岩岩庖\n",
        "征岩岩岩忽\n",
});


int init_tab();
int do_display(string arg);
int do_move(string arg);
int do_toss();
string long();
string query_save_file();
void do_check();
int do_save();
int do_deploy();

void create()
{
        set_name("笢弊砓攫", ({ "chinese chess board","ccb","board" }) );
        set_weight(3000000);
        set_max_encumbrance(0);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桲");
                set("long", "涴岆珨桲笢弊砓攫ㄛ蚚懂狟砓腔﹝\n");
                set("value", 0);
                set("material", "wood");
                set("no_get",1);
                set("no_drop",1);
        }
        setup();
}
void init()
{
        init_tab();
        add_action("do_move","move");   
        add_action("do_toss","toss");
        add_action("do_reset","reset");
        add_action("do_save","csave");
        add_action("do_deploy","deploy");
        add_action("do_lose","lose");
        add_action("do_help","help");
        add_action("do_review","review");
}

string query_save_file()
{ 
        if( bb == 1 )
                return DATA_DIR+"cchess/"+query("id", this_player())[0..0]+"/"+query("id", this_player());
        else
                return DATA_DIR + "cchess/cchess"; 
}

int init_tab()
{
        table = keys(TABLE);
        table = sort_array(table,1);
        return 1;
}

int do_move(string arg)
{
        int sROW,sCOL,tROW,tCOL,i,ii,x,y,tem,tem1,tem2,tem3,tem4;
        string msg,msg1;
        object ob,me; 
        ob = this_object();
        me = this_player();
        msg1 = "";

        if( query("over", ob))return notify_fail("涴攫眒冪賦旰賸﹝\n");

        if( me->name() != query("name1", ob) && me->name() != query("name2", ob) )
                return notify_fail("斕遜岆珂芘鷋赽勘ㄐ\n");

        if( !query("name2", ob) )
                return notify_fail("遜猁衄珨跺符夔狟ㄐ\n");

        if( query("round", ob) == 0 && query("first", ob) != me->name() )
                return notify_fail("涴跺隙磁祥蜆斕軗ㄐ\n");

        if( query("round", ob) == 1 && query("first", ob) == me->name() )
                return notify_fail("涴跺隙磁祥蜆斕軗ㄐ\n");

        if( !arg ) return notify_fail("痄雄赽ㄩmove 筵釴梓 軝釴梓 to 筵釴梓 軝釴梓 \n");

        if( sscanf(arg,"%d %d to %d %d",sCOL,sROW,tCOL,tROW) != 4 )
                return notify_fail("痄雄赽ㄩmove 筵釴梓 軝釴梓 to 筵釴梓 軝釴梓 \n");

        if( tCOL > 9 || tCOL < 1 || tROW > 9 || tROW < 0 || sCOL > 9 || sCOL < 1 || sROW > 9 || sROW < 0)
                return notify_fail("斕腔怀眒冪閉埣砓攫賜盄賸﹝\n");

        if( tCOL == sCOL && sROW == tROW )
                return notify_fail("涴遜蚚痄雄鎘ˋ\n");

        sCOL -= 1;
        tCOL -= 1;

        sROW = sROW * 2;
        tROW = tROW * 2;
        sCOL = sCOL * 2;
        tCOL = tCOL * 2;

        if( TABLE[table[sROW]][sCOL][1] == "  " )
                return notify_fail("涴跺華源羶衄赽﹝\n");

        if( TABLE[table[tROW]][tCOL][3] == TABLE[table[sROW]][sCOL][3] )
                return notify_fail("斕猁勛裁赻撩腔赽ˋ\n");

        if( query("round", ob) == 0 && cc != 1 )
                return notify_fail("斕鏽渣赽賸勘ㄐ\n");

        if( query("round", ob) == 1 && cc != 2 )
                return notify_fail("斕鏽渣赽賸勘ㄐ\n");


//陬 
        if( che == 1 )
        {
                if( tCOL != sCOL && sROW != tROW )
                        return notify_fail("涴跺赽硐夔軗眻盄﹝\n");

                if( tCOL > sCOL && tCOL - sCOL > 2 )
                        for (i=sCOL+2;i<tCOL;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[sROW]][i][1] != "  " )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }

                if( sCOL > tCOL && sCOL - tCOL > 2 )
                        for (i=tCOL+2;i<sCOL;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[sROW]][i][1] != "  " )
                                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }

                if( tROW > sROW && tROW - sROW > 2  )
                        for (i=sROW+2;i<tROW;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[i]][sCOL][1] != "  " )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }

                if( sROW > tROW && sROW - tROW > 2 )
                        for (i=tROW+2;i<sROW;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[i]][sCOL][1] != "  " )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }
        }

//鎮
        if( che == 2 )
        {
                if( tCOL==sCOL || sROW==tROW )
                        return notify_fail("鎮祥夔軗眻盄﹝\n");

                if( tCOL<(sCOL-4) || tCOL>(sCOL+4) || tROW<(sROW-4) || tROW>(sROW+4))
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( (tCOL==sCOL-2 || tCOL==sCOL+2) && (tROW!=sROW-4 && tROW!=sROW+4))
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( (tCOL==sCOL-4 || tCOL==sCOL+4) && (tROW!=sROW-2 && tROW!=sROW+2))
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( sCOL-tCOL < -2 && TABLE[table[sROW]][sCOL+2][1] != "  ")
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( sCOL-tCOL > 2 && TABLE[table[sROW]][sCOL-2][1] != "  ")
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( sROW-tROW > 2 && TABLE[table[sROW-2]][sCOL][1] != "  ")
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( sROW-tROW < -2 && TABLE[table[sROW+2]][sCOL][1] != "  ")
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
        }
//眈
        if( che == 3 )
        {
                if( tCOL == sCOL || sROW == tROW )
                        return notify_fail("眈祥夔軗眻盄﹝\n");

                if( (tROW!=sROW-4 && tROW!=sROW+4) || (tCOL!=sCOL-4 && tCOL!=sCOL+4))
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( tCOL > sCOL )
                {
                        if( tROW > sROW && TABLE[table[sROW+2]][sCOL+2][1] != "  " )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                        if( tROW < sROW && TABLE[table[sROW-2]][sCOL+2][1] != "  " )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }

                if( tCOL < sCOL )
                {
                        if( tROW > sROW && TABLE[table[sROW+2]][sCOL-2][1] != "  " )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                        if( tROW < sROW && TABLE[table[sROW-2]][sCOL-2][1] != "  " )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }

                if( (cc == 1 && tROW > 9) || (cc == 2 && tROW < 9) )
                        return notify_fail("眈祥夔徹碩﹝\n");
        }
//帊
        if( che == 4 )
        { 
                if( tCOL == sCOL || sROW == tROW )
                        return notify_fail("帊祥夔軗眻盄﹝\n");

                if( (tROW!=sROW-2 && tROW!=sROW+2) || (tCOL!=sCOL-2 && tCOL!=sCOL+2))
                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( cc == 1 && (tCOL > 10 || tCOL < 6 || tROW > 4))
                        return notify_fail("饒跺弇离閉堤帊痄雄腔毓峓賸﹝\n");

                if( cc == 2 && (tCOL > 10 || tCOL < 6 || tROW < 14))
                        return notify_fail("饒跺弇离閉堤帊痄雄腔毓峓賸﹝\n");
        }
//邟
        if( che == 5 )
        {
                if( tCOL != sCOL && sROW != tROW )
                        return notify_fail("涴跺赽硐夔軗眻盄﹝\n");

                if( tCOL-sCOL>2 || tCOL-sCOL<-2 || tROW-sROW>2 || tROW-sROW<-2)
                        return notify_fail("邟珨棒硐夔軗珨跡﹝\n");

                if( cc == 1 )
                        if( tCOL > 10 || tCOL < 6 || tROW > 4 )
                                return notify_fail("饒跺弇离閉堤邟痄雄腔毓峓賸﹝\n");

                if( cc == 2 )
                        if( tCOL > 10 || tCOL < 6 || tROW < 14 )
                                return notify_fail("饒跺弇离閉堤邟痄雄腔毓峓賸﹝\n");
        }
//蘿
        if( che == 6 )
        {
                ii = 0;
                if( tCOL != sCOL && sROW != tROW )
                        return notify_fail("涴跺赽硐夔軗眻盄﹝\n");

                if( cc1 != 0 )
                        if( tCOL-sCOL==2 || tCOL-sCOL==-2 || tROW-sROW==2 || tROW-sROW==-2)
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");

                if( tCOL > sCOL )
                {
                        for (i=sCOL+2;i<tCOL;i++)
                        {
                                if(i%2!=0) continue;
                                if( TABLE[table[sROW]][i][1] != "  " )
                                        ii += 1;
                                if( ii > 1 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                                if( ii == 1 && cc1 == 0 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }
                        if( ii == 0 && cc1 != 0 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }

                if( sCOL > tCOL )
                {
                        for (i=tCOL+2;i<sCOL;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[sROW]][i][1] != "  " )
                                        ii += 1;
                                if( ii > 1 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                                if( ii == 1 && cc1 == 0 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }
                        if( ii == 0 && cc1 != 0 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }

                if( tROW > sROW && tROW - sROW > 2  )
                {
                        for (i=sROW+2;i<tROW;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[i]][sCOL][1] != "  " )
                                        ii += 1;
                                if( ii > 1 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                                if( ii == 1 && cc1 == 0 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }
                        if( ii == 0 && cc1 != 0 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }

                if( sROW > tROW && sROW - tROW > 2 )
                {
                        for (i=tROW+2;i<sROW;i++)
                        {
                                if( i%2!=0) continue;
                                if( TABLE[table[i]][sCOL][1] != "  " )
                                        ii += 1;
                                if( ii > 1 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                                if( ii == 1 && cc1 == 0 )
                                        return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                        }
                        if( ii == 0 && cc1 != 0 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }
        }

//條
        if( che == 7 )
        {
                if( tCOL-sCOL>2 || tCOL-sCOL<-2 || tROW-sROW>2 || tROW-sROW<-2)
                        return notify_fail("條珨棒硐夔軗珨跡﹝\n");
                if( tCOL != sCOL && sROW != tROW )
                        return notify_fail("涴跺赽硐夔軗眻盄﹝\n");
                if( cc == 1 )
                {
                        if( sROW > tROW ) return notify_fail("條祥夔厘隙軗﹝\n");
                        if( tCOL != sCOL && sROW < 9 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }
                if( cc == 2 )
                {
                        if( sROW < tROW ) return notify_fail("條祥夔厘隙軗﹝\n");
                        if( tCOL != sCOL && sROW > 9 )
                                return notify_fail("涴跺赽祥夔痄雄善饒跺華源﹝\n");
                }
        }

        if ( TABLE[table[tROW]][tCOL][2] != 0 )
        {
                msg1+="$N勛裁賸勤忒珨跺"+sprintf("%s﹝\n",TABLE[table[tROW]][tCOL][1]);
                if( cc1 == 1 )
                        bche+=TABLE[table[tROW]][tCOL][1];
                else
                        rche+=TABLE[table[tROW]][tCOL][1];
        }

        if ( TABLE[table[tROW]][tCOL][2] == 5 )
        {
                msg1 += HIY"$N荇腕賸涴部掀腔吨瞳﹝\n"NOR;
                set("over", this_player()->name(), ob);
        }

        TABLE[table[tROW]][tCOL][1] = TABLE[table[sROW]][sCOL][1];
        TABLE[table[tROW]][tCOL][2] = TABLE[table[sROW]][sCOL][2];
        TABLE[table[tROW]][tCOL][3] = TABLE[table[sROW]][sCOL][3];
        TABLE[table[sROW]][sCOL][1] = "  ";
        TABLE[table[sROW]][sCOL][2] = 0; 
        TABLE[table[sROW]][sCOL][3] = 0; 

        tem4 = 0;
        for( y=0;y<6;y++ )
        {
                if( y%2 != 0 ) continue;
                for( x=6;x<12;x++ )
                {
                        if( x%2 != 0 ) continue;
                        if( TABLE[table[y]][x][2] == 5 )
                        {
                                tem = x;
                                tem3 = y;
                                break;
                        }
                }
        }

        for( y=14;y<19;y++ )
        {
                if( y%2 != 0 ) continue;
                for( x=6;x<12;x++ )
                {
                        if( x%2 != 0 ) continue;
                        if( TABLE[table[y]][x][2] == 5 )
                        {
                                tem1 = x;
                                tem2 = y;
                                break;
                        }
                }
        }

        if( tem == tem1 )
        {
                for (i=tem3+2;i<tem2;i++)
                {
                        if( i%2!=0) continue;
                        if( TABLE[table[i]][tem][1] != "  " )
                        tem4 = 1; 
                }
                if( tem4 == 0 )
                {
                        msg1 += (sprintf(HIY"%s荇腕賸涴部掀腔吨瞳﹝\n"NOR,
                        query("name1", ob) == me->name()?query("name2", ob):
                        query("name1", ob)));
                        ob->set("over",query("name1",ob) == me->name()?query("name2",ob):
                        query("name1", ob));
                }
        }

        if( sROW == tROW )
                if( cc1 == 2 )
                        msg = sprintf("◇%s◆%s%s", TABLE[table[tROW]][tCOL][1], chinese_number(sCOL/2+1), chinese_number(tCOL/2+1) );
                else
                        msg = sprintf("◇%s◆%s%s", TABLE[table[tROW]][tCOL][1], chinese_number(10-(sCOL/2+1)), chinese_number(10-(tCOL/2+1)) );

        else 
                if( cc1 == 2 )
                        if( sROW>tROW )
                                msg = sprintf("◇%s◆%s輛%s", TABLE[table[tROW]][tCOL][1], chinese_number(sCOL/2+1), sCOL==tCOL?chinese_number( (sROW-tROW)/2 ):chinese_number(tCOL/2+1) );
                        else
                                msg = sprintf("◇%s◆%s豖%s", TABLE[table[tROW]][tCOL][1], chinese_number(sCOL/2+1), sCOL==tCOL?chinese_number( (tROW-sROW)/2 ):chinese_number(tCOL/2+1) );
                else 
                        if( tROW>sROW )
                                msg = sprintf("◇%s◆%s輛%s", TABLE[table[tROW]][tCOL][1], chinese_number(10-(sCOL/2+1)), sCOL==tCOL?chinese_number( (tROW-sROW)/2 ):chinese_number(10-(tCOL/2+1)) );
                        else
                                msg = sprintf("◇%s◆%s豖%s", TABLE[table[tROW]][tCOL][1], chinese_number(10-(sCOL/2+1)), sCOL==tCOL?chinese_number( (sROW-tROW)/2 ):chinese_number(10-(tCOL/2+1)) );

        message_vision( "$N狟賸珨覂"+msg+"\n",this_player());
        message_vision( msg1,me);

        do_check();

        if( aa == 4 )
        {
                aaa += msg+"\n"; 
                aa = 0;
        } else
        {
                aaa += msg+" ";
                aa += 1;
        }

        query("round",ob) == 1?set("round",0,ob):set("round",1,ob); 
        return 1;
}

int do_toss()
{
        int num;
        string text;
        object me, ob;
        me = this_player();
        ob = this_object();

        if( query("name2", ob) )
                return notify_fail("眒冪衄謗跺婓狟賸﹝\n");

        if( me->name() == query("name1", ob) )
                return notify_fail("斕眒冪芘徹珨棒鷋赽賸﹝\n");

        num = random(6);

        if( query("num", ob) == num)num=random(6);

        text = "鏽鷋赽婓忒笢牷賸謗牷, 祣堤賸珨跺ㄩ\n";
        text += tossText[6]+tossText[num]+tossText[7];
        message_vision( "$N"+text,me );

        if( query("name1", ob) )
        {
               query("num",ob)>num?set("first",query("name1",ob),ob):set("first",me->name(),ob); 
                message_vision(query("first", ob)+"妏蚚綻伎赽珂俴﹝\n",me);
        }

        set("num", num, ob);
        query("name1",ob)?set("name2",me->name(),ob): set("name1",me->name(),ob); 
        query("id1",ob)?set("id2",query("id",me),ob):set("id1",query("id",me),ob); 

        return 1;
}

string long()
{
        int row,col,i;
        string text,round,msg;
        object ob,me;
        ob = this_object();
        me = this_player();
        text = "\n1   2   3   4   5   6   7   8   9\n";
        msg=query("name1", ob) == query("first", ob)?query("name2", ob):query("name1", ob);

        if( query("name2", ob) )
        {
                if( query("over", ob) )
                        round="涴攫"+query("over", ob)+"荇賸﹝";
                else
                        if( query("round", ob) == 1 )
                                round = " 珋婓謫善"+HIC"懦赽"NOR+"狟";
                        else
                                round = " 珋婓謫善"+HIR"綻赽"NOR+"狟";
                TABLE[table[9]][0][1] = sprintf("%s%s",TABLE[table[9]][0][0],round );
        }

        if( me->name() != query("first", ob) )
        {
                TABLE[table[17]][0][1] = "岱";
                TABLE[table[3]][0][1] = "岱";
                TABLE[table[5]][0][1] = "岱";
                TABLE[table[13]][0][1] = "岱";
                TABLE[table[15]][0][1] = "岱";
                TABLE[table[0]][0][0] = "庚";
                TABLE[table[10]][0][0] = "庚";
                TABLE[table[0]][16][0] = "庖";
                TABLE[table[10]][16][0] = "庖";
                TABLE[table[18]][16][0] = "彼";
                TABLE[table[8]][16][0] = "彼";
                TABLE[table[8]][0][0] = "弩";
                TABLE[table[18]][0][0] = "弩";
                TABLE[table[2]][16][0] = TABLE[table[4]][16][0]
                                = TABLE[table[6]][16][0] = TABLE[table[12]][16][0]
                                = TABLE[table[14]][16][0] = TABLE[table[16]][16][0]
                                = "怕";
                TABLE[table[2]][0][0] = TABLE[table[4]][0][0]
                                = TABLE[table[6]][0][0] = TABLE[table[12]][0][0]
                                = TABLE[table[14]][0][0] = TABLE[table[16]][0][0]
                                = "念";

                TABLE[table[1]][16][1] = "岱 衄恀枙ㄛ統艘※help cchess§";
                TABLE[table[15]][16][1] = sprintf("%s%s%s",TABLE[table[15]][16][0]," ",bche );
                TABLE[table[5]][16][1] = sprintf("%s%s%s",TABLE[table[5]][16][0]," ",rche);

                if( query("name2", ob) )
                {
                        TABLE[table[3]][16][1]=sprintf("%s%s%s","岱","("+query("first", ob)+")",HIR"綻源"NOR+"垀勛赽ㄩ");
                        TABLE[table[13]][16][1] = sprintf("%s%s%s","岱"," ("+msg+") ",HIC"懦源"NOR+"垀勛赽ㄩ" );
                }

                for( i=2;i<16;i++)
                {
                        if( i%2!=0) continue;
                        TABLE[table[8]][i][0] = "拂";
                        TABLE[table[10]][i][0] = "房";
                        TABLE[table[18]][i][0] = "拂";
                        TABLE[table[0]][i][0] = "房";
                }

                for( row=0; row<sizeof(table); row++ )
                {
                        for( col=0; col<sizeof(TABLE[table[row]]); col++ )
                        {
                                if( TABLE[table[row]][col][1] == "  " )
                                        text += sprintf("%s", TABLE[table[row]][col][0] );
                                else
                                        text += sprintf("%s", TABLE[table[row]][col][1] );
                        }
                        if( row%2 == 0)
                                text += sprintf(" %d", row/2 );
                        text += "\n";
                }
        } else
        {
                text = "\n9   8   7   6   5   4   3   2   1\n";
                TABLE[table[1]][16][1] = "岱";
                TABLE[table[3]][16][1] = "岱";
                TABLE[table[5]][16][1] = "岱";
                TABLE[table[13]][16][1] = "岱";
                TABLE[table[15]][16][1] = "岱";
                TABLE[table[0]][0][0] = "彼";
                TABLE[table[18]][16][0]= "庚";
                TABLE[table[0]][16][0] = "弩";
                TABLE[table[18]][0][0] = "庖";
                TABLE[table[8]][16][0] = "庚";
                TABLE[table[10]][16][0] = "弩";
                TABLE[table[2]][16][0] = TABLE[table[4]][16][0]
                        = TABLE[table[6]][16][0] = TABLE[table[12]][16][0]
                        = TABLE[table[14]][16][0] = TABLE[table[16]][16][0]
                        = "念";
                TABLE[table[10]][0][0] = "忠";
                TABLE[table[8]][0][0] = "庖";
                TABLE[table[2]][0][0] = TABLE[table[4]][0][0]
                        = TABLE[table[6]][0][0] = TABLE[table[12]][0][0]
                        = TABLE[table[14]][0][0] = TABLE[table[16]][0][0]
                        = "怕";

                TABLE[table[17]][0][1] = "岱 衄恀枙ㄛ統艘※help cchess§";
                TABLE[table[13]][0][1] = sprintf("%s%s%s",TABLE[table[15]][16][0]," ",bche);
                TABLE[table[3]][0][1] = sprintf("%s%s%s",TABLE[table[5]][16][0]," ",rche);

                if( query("name2", ob) )
                {
                        TABLE[table[5]][0][1]=sprintf("%s%s%s","岱","("+query("first", ob)+")",HIR"綻源"NOR+"垀勛赽ㄩ");
                        TABLE[table[15]][0][1] = sprintf("%s%s%s","岱"," ("+msg+") ",HIC"懦源"NOR+"垀勛赽ㄩ" );
                }

                for( i=2;i<16;i++)
                {
                        if( i%2!=0) continue;
                        TABLE[table[8]][i][0] = "房";
                        TABLE[table[10]][i][0] = "拂";
                        TABLE[table[18]][i][0] = "房";
                        TABLE[table[0]][i][0] = "拂";
                }

                for( row=(sizeof(table)-1); row>-1; row-- )
                {
                        for( col=(sizeof(TABLE[table[row]])-1); col>-1; col-- )
                        {
                                if( TABLE[table[row]][col][1] == "  " )
                                        text += sprintf("%s", TABLE[table[row]][col][0] );
                                else
                                        text += sprintf("%s", TABLE[table[row]][col][1] );
                        }
                        if( row%2 == 0)
                                text += sprintf(" %d", row/2 );
                        text += "\n";
                }
        }
        return text;
}
void do_check()
{
        int x,y,tem,tem1,i,tem3,check;
        object ob = this_object();
        check = 0;

        if( query("over", ob))return ;
        if( query("round", ob) == 1 )
        for( y=0;y<5;y++ )
        {
                if( y%2 != 0 ) continue;
                for( x=6;x<11;x++ )
                {
                        if( x%2 != 0 ) continue;
                        if( TABLE[table[y]][x][2] == 5 )
                        {
                                tem = x;
                                tem1 = y;
                                break;
                        }
                }
        }
        else
                for( y=14;y<19;y++ )
                {
                        if( y%2 != 0 ) continue;
                        for( x=6;x<11;x++ )
                        {
                                if( x%2 != 0 ) continue;
                                if( TABLE[table[y]][x][2] == 5 )
                                {
                                        tem = x;
                                        tem1 = y;
                                        break;
                                }
                        }
                }

        if( tem1 < 9 )
                if( TABLE[table[tem1+2]][tem][2] == 7 && TABLE[table[tem1+2]][tem][3] != TABLE[table[tem1]][tem][3] )
                        check = 1;

        if( tem1 > 9 )
                if( TABLE[table[tem1-2]][tem][2] == 7 && TABLE[table[tem1-2]][tem][3] != TABLE[table[tem1]][tem][3] )
                        check = 1;

        if( TABLE[table[tem1]][tem+2][2] == 7 )
                check = 1;

        if( TABLE[table[tem1]][tem-2][2] == 7 )
                check = 1;

        tem3 = 0;
        for (i=tem+2;i<17;i++)
        {
                if( i%2!=0) continue;
                if( tem3 == 1 && TABLE[table[tem1]][i][2] == 6 )
                        if( TABLE[table[tem1]][i][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[tem1]][i][2] == 1 && tem3 == 0 )
                        if( TABLE[table[tem1]][i][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[tem1]][i][2] != 0 )
                        tem3 += 1;
        }

        tem3 = 0;
        for (i=tem-2;i>-1;i--)
        {
                if( i%2!=0) continue;
                if( tem3 == 1 && TABLE[table[tem1]][i][2] == 6 )
                        if( TABLE[table[tem1]][i][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[tem1]][i][2] == 1 && tem3 == 0 )
                        if( TABLE[table[tem1]][i][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[tem1]][i][2] != 0 )
                        tem3 += 1;
        }

        tem3 = 0;
        for (i=tem1-2;i>-1;i--)
        {
                if( i%2!=0) continue;
                if( tem3 == 1 && TABLE[table[i]][tem][2] == 6 )
                if( TABLE[table[i]][tem][3] != TABLE[table[tem1]][tem][3] )
                {
                        check = 1;
                        break;
                }
                if( TABLE[table[i]][tem][2] == 1 && tem3 == 0 )
                        if( TABLE[table[i]][tem][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[i]][tem][2] != 0 )
                        tem3 += 1;
        }

        tem3 = 0;
        for (i=tem1+2;i<19;i++)
        {
                if( i%2!=0) continue;
                if( tem3 == 1 && TABLE[table[i]][tem][2] == 6 )
                        if( TABLE[table[i]][tem][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[i]][tem][2] == 1 && tem3 == 0 )
                        if( TABLE[table[i]][tem][3] != TABLE[table[tem1]][tem][3] )
                        {
                                check = 1;
                                break;
                        }
                if( TABLE[table[i]][tem][2] != 0 )
                        tem3 += 1;
        }

        if( tem1 > 1 )
        {
                if( TABLE[table[tem1-2]][tem-2][2] == 0 )
                {
                        if( tem1 > 2 )
                                if( TABLE[table[tem1-4]][tem-2][2] == 2 && TABLE[table[tem1-4]][tem-2][3] != TABLE[table[tem1]][tem][3] )
                                        check = 1; 
                        if( TABLE[table[tem1-2]][tem-4][2] == 2 && TABLE[table[tem1-2]][tem-4][3] != TABLE[table[tem1]][tem][3] )
                                check = 1;
                }
                if( TABLE[table[tem1-2]][tem+2][2] == 0 )
                {
                        if( tem1 > 2 )
                                if( TABLE[table[tem1-4]][tem+2][2] == 2 && TABLE[table[tem1-4]][tem+2][3] != TABLE[table[tem1]][tem][3] )
                                        check = 1; 
                        if( TABLE[table[tem1-2]][tem+4][2] == 2 && TABLE[table[tem1-2]][tem+4][3] != TABLE[table[tem1]][tem][3] )
                                check = 1;
                }
        }

        if( tem1 < 17 )
        {
                if( TABLE[table[tem1+2]][tem-2][2] == 0 )
                {
                        if( tem1 < 16 )
                                if( TABLE[table[tem1+4]][tem-2][2] == 2 && TABLE[table[tem1+4]][tem-2][3] != TABLE[table[tem1]][tem][3] )
                                        check = 1; 
                        if( TABLE[table[tem1+2]][tem-4][2] == 2 && TABLE[table[tem1+2]][tem-4][3] != TABLE[table[tem1]][tem][3] )
                                check = 1;
                } 
                if( TABLE[table[tem1+2]][tem+2][2] == 0 )
                {
                        if( tem1 < 16 )
                                if( TABLE[table[tem1+4]][tem+2][2] == 2 && TABLE[table[tem1+4]][tem+2][3] != TABLE[table[tem1]][tem][3] )
                                        check = 1;
                        if( TABLE[table[tem1+2]][tem+4][2] == 2 && TABLE[table[tem1+2]][tem+4][3] != TABLE[table[tem1]][tem][3] )
                                check = 1;
                }
        }

        if( check ) message_vision("$N佽耋"+HIG"※蔚濂ㄐㄐ§\n"NOR,this_player() );
}

int do_save()
{
        bb = 1;
        save();
        write("暮翹俇救﹝\n");
        return 1;
}

int do_deploy()
{
        object me,ob;
        me = this_player();
        ob = this_object();
        bb = 1; 

        if( query("id1", ob) )
                if( (query("id2", present(query("id1", ob),environment(ob))) || (present(ob),environment(ob))) )
                        if( me->name() != query("name1", ob) && me->name() != query("name2", ob) && !query("over", ob) )
                                return notify_fail("掀遜婓輛俴笢ㄛ斕祥夔觴雄攫ㄐ\n"); 

        if( !restore() ) return notify_fail("斕醴羶衄槨翹腔紹擁﹝\n");

        setup();
        write("OKㄐ\n");
        return 1;
}

int do_lose()
{
        object ob,me;
        ob = this_object();
        me = this_player();

        if( me->name() != query("name1", ob) && me->name() != query("name2", ob) )
                return notify_fail("斕甜羶衄婓狟﹝\n"); 

        if( query("over", ob) )
                return notify_fail("涴攫眒冪賦旰賸﹝\n"); 

        if( bche == "" && rche == "" )
                return notify_fail("涴欴憩怀賸?\n"); 

        message_vision(HIW"$N酗抩珨汒※...扂怀賸ㄐ...§\n"NOR,this_player());
        ob->set("over",query("name1",ob) == me->name()?query("name2",ob):
        query("name1", ob));

        return 1;
}

int do_help(string arg)
{
        if( arg == "cchess" )
        {
                write(sprintf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
"〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞",
"笢弊砓ㄗcchessㄘ",  
"〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞〞",
"狟赽        ㄩmove <筵釱梓> <軝釱梓> to <筵釱梓> <軝釱梓>",
"笭狟        ㄩreset",
"黍堤紹擁    ㄩdeploy",
"暮翹紹擁    ㄩcsave",
"祣鷋珂俴ㄩtoss",
"隙嘈        ㄩreview",
"怀        ㄩlose",
"夤艘擁    ㄩlook麼l board麼ccb",
)
); 
                return 1;
        }
}

int do_review()
{
        write("醴軗徹腔赽﹝\n");
        write(aaa+"\n");
        return 1;
}

int do_reset()
{
        object me,ob;
        me = this_player();
        ob = this_object();
        bb = 0;

        if( query("id2", ob) )
                if( (present(query("id1", ob),environment(ob))) || (present(query("id2", ob),environment(ob))) )
                        if( me->name() != query("name1", ob) && me->name() != query("name2", ob) && !query("over", ob) )
                                return notify_fail("掀遜婓輛俴笢ㄛ斕祥夔觴雄攫ㄐ\n"); 
        if( restore() )
        {
                setup();
                message_vision( "$N參攫笭陔啊疑賸﹝\n",this_player());
        }
        return 1;
}