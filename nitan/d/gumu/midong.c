// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "河底密洞");
        set("long", @LONG
這裏是一座不大的石洞，四周是堅硬的石壁(wall)，看來想要出
去真是難如登天的了。室內只有一牀一案，一縷陽光從洞頂的巖縫中
射入，室內光線明亮。牆邊有一個青石牀 (bed)，與旁邊石壁的色澤
有很大不同。透過斜射的陽光，你看到石牀對面牆壁上似乎刻着一些
文字和圖形。一個寬大的石案上擺着一個石匣(xia)。
LONG
        );
        set("sleep_room", 1);

        set("item_desc",([
                "wall":"\n       只見石壁上刻着“劍動莫名”四個龍飛鳳舞的大字。\n
下面有三個持劍捏訣的人像，刻得栩栩如生，每個人姿勢都不相同。\n
       旁邊還有許多小字,你不妨照着練習(lianxi)一下。\n ",
                "牆壁":"\n       只見石壁上刻着“劍動莫名”四個龍飛鳳舞的大字。\n
下面有三個持劍捏訣的人像，刻得栩栩如生，每個人姿勢都不相同。\n
       旁邊還有許多小字，你不妨照着練習(lianxi)一下。\n ",
                "bed":"\n一個普普通通的石牀。\n ",
                "xia":"\n一隻石匣，好像是和石案連在一起的，不知道敢不敢打開看看。\n ",
        ]));

        set("mishi_sword",1);
        setup();
}

void init()
{
        add_action("do_lianxi", "lianxi");
        add_action("do_jump", "jump");
        add_action("do_open", "open");
}

int do_lianxi(string arg)
{

        object me=this_player();
        int swordskill=(int)me->query_skill("sword", 1);
        int wumingskill=(int)me->query_skill("wuming-jianfa", 1);
        int exp=(int)query("combat_exp", me);

        if( query("jing", me)<query("max_jing", me)/5 )
                return notify_fail("你已經沒有精力練習了！\n");

        if( !query_temp("wuming_onbed", me) )
        {
                message_vision("$N手捏劍訣，照着壁上的圖形比劃了幾次，只覺得一陣口乾舌燥。\n", me);
        }
        else
        {
                message_vision("$N手捏劍訣照着壁上圖形的姿勢比劃了幾次，腦中靈光一閃似乎領悟到了什麼。\n", me);
                if (wumingskill>300)
                        return notify_fail("你照着壁上圖形比劃了兩下，覺得似乎沒什麼可領悟的了。\n");
                if (exp <= (wumingskill*wumingskill*wumingskill)/10)
                {
                        me->receive_damage("qi", 30);
                        return notify_fail("但是你的經驗不夠，始終不能從圖中領悟到什麼。\n");
                }
                if (wumingskill >150 && swordskill>150 )
                {
                        me->improve_skill("wuming-jianfa", (int)(me->query_int()));
                        tell_object(me, "你似乎從中領悟出一些無名劍法方面的竅門。\n");
                }
                else
                {
                        tell_object(me, "你的功夫太低了，還不能領會圖形所載的練功法門。\n");
                }
        }
        me->receive_damage("jing", 30);
        return 1;
}

int do_jump(string arg)
{
        object me=this_player();

        if( !arg ||! (arg =="bed" || arg =="up" || arg =="down"))
                return 0;

        if( arg =="up"||arg=="bed")
        {
                if( query_temp("wuming_onbed", me) )
                        return notify_fail("你已經在牀上了，再跳就碰到洞頂了。\n");
                set_temp("wuming_onbed", 1, me);
                message_vision("$P輕輕一縱跳上了石牀，坐了下來。\n", me);
                tell_object(me, "你只覺得一絲絲涼氣從身下傳來，頓絕精神一振。\n");
        }

        if( arg =="down"){
                if( !query_temp("wuming_onbed", me) )
                        return notify_fail("你已經在地下了，亂蹦亂跳成何體統？\n");
                delete_temp("wuming_onbed", me);
                message_vision("$P從石牀上跳了下來。\n", me);
        }
        return 1;
}

int valid_leave (object me, string dir)
{
        if( query_temp("wuming_onbed", me) )
                return notify_fail("先下牀再走，連走路也不會嗎？\n");
        return 1;
}

int do_open(string arg)
{
        object me,ob;

        me=this_player();
        if( !arg || arg !="xia")
                return 0;

        if( query("mishi_sword") < 1)
                return notify_fail("你打開石匣。但見裏面空空如也。\n");

        addn("mishi_sword", -1);
        message_vision(YEL"$P打開石匣，從裏面取出一把"HIR"越女"HIY"朝陽"HIC"劍。\n"NOR, me);
        ob = new("/clone/lonely/yuenv");
        ob->move(me);
        message_vision(HIM"突然憑空捲起一陣狂風,冥冥中響起一個空洞的聲音:神技橫空,劍贈有緣!去吧.....\n"
                       HIY"呼嘯聲中,$N的身形已被捲上半空.\n"NOR, me);
        me->move("/d/taohua/lantian");
        return 1;
}

