// Room: /binghuo/boat1.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", "帆船");
        set("long", @LONG
這是一艘三桅海船，不知船主是誰。船上前後兩桅掛了白帆，準
備出海。船中艙中備有糧水，足夠支用半年。船上水手個個都是啞巴。
主桅(gui) 空懸一條纜繩，隨風不住舞動。
LONG );
        set("outdoors", "lingshe");
        set("item_desc", ([
                "gui" : "海船上的主桅，可以掛帆。\n",
        ]));
        set("exits", ([
                "out" : __DIR__"lingshegang",
        ]));
        setup();
}

void init()
{
        add_action("do_gua", "gua");
        add_action("do_gua", "hang");
}
int do_gua ( string arg )
{
        object ob ;
        string dir;
        if( !arg || (arg !="fan" && arg != "fan bu")) 
        {
                tell_object(this_player() , "你要掛啥呢？瞎折騰！\n" ) ;
                return 1 ;
        }
        ob = this_player ();
        if (!(present("fan bu", ob)))
        {
                tell_object(this_player() , "帆布在哪？你四下一望，沒見着！\n");
                return 1 ;
        }
        message_vision("$N掛起主帆，船頭緩緩轉過，向北航行。\n", ob);
        ob ->move(__DIR__"northboat2") ;
        tell_object(ob, BLU "海風一陣陣從艙口中吹了進來，你感到陣陣寒意.......\n" NOR ) ;
        call_out("north1", 10 , ob );
        return 1 ;
}
void north1( object ob )
{
        tell_object(ob , BLU
"突然之間，你身子一側，滾了幾個轉身，但聽得水手同時大叫，
呼喝聲中又夾着疾風呼嘯，波浪轟擊之聲，似乎千百個巨浪同
時襲到。你只感全身一涼，口中鼻中全是鹽水，當即掙扎着站
起。腳底下艙板斗然間向左側去，船中的海水又向外倒瀉，但
聽得狂風呼嘯，身周盡是海水。
    但聽喀喇喇、喀喇喇幾聲猛響，主桅和前桅先後折斷。兩
條桅杆帶着白帆，跌入海中。\n" NOR);
        ob->move (__DIR__"northboat3") ;
        tell_object(ob , BLU
"又是一個浪頭撲將上來，這巨浪猶似一堵結實的水牆，砰的一
聲大響，只打得船木橫飛。\n" NOR) ;
        if( query("neili", ob)<300 )
        {
                tell_object(ob , HIR
"\n驀地裏一個巨浪飛到，將你衝出船舷之外。這個浪頭來得極其
突兀，你全然的猝不及防。待得驚覺，已是身子凌空，這一落
下去，腳底便是萬丈洪濤......\n" NOR) ;
                ob->unconcious();
                ob->move("/d/quanzhou/houzhu");
        }
        else call_out("north2", 10 , ob);
}
void north2( object ob )
{
        tell_object(ob , BLU
"船上的艙蓋、甲板均被打得破碎不堪，船身卻仍無恙。頭頂烏
雲滿天，大雨如注，四下裏波濤山立，這當兒根本分不出東南
西北。船身一時如上高山，片刻間似瀉深谷，桅檣盡折，船隻
也已無法駕駛。\n" NOR);
        ob->move (__DIR__"northboat4") ;
        tell_object(ob , BLU
"海流一直向北，帶着船隻日夜不停的北駛。夜晚北極星總是在
船頭之前閃爍，太陽總是在右舷方升起，在左舷方落下，連續
十餘日，船行始終不變。\n" NOR);
        call_out("north3", 10 , ob );
}
void north3( object ob )
{
        tell_object(ob , BLU
"氣候卻一天天的寒冷起來，你也一天比一天憔悴。眼看座船再
北行數日，非凍死你不可。\n"NOR);
        call_out("north4", 10 , ob );
}
void north4( object ob )
{
        tell_object(ob , BLU
"這船日夜不停的向北駛去，越北越冷，此刻海中出現小小碎冰，
日後勢必滿海是冰，座船一給凍住，移動不得，那便是你畢命
之時了。只是聽着丁冬、丁冬，冰塊互相撞擊的聲音，一夜不
寐。\n"NOR);
        call_out("north5", 10 , ob );
}
void north5( object ob )
{
        tell_object(ob , BLU
"次日上午，海上冰塊已有碗口大小，撞在船上，拍拍作響。海
面浮冰或如桌面，或如小屋，忽聽得轟的一聲巨響，船身劇烈
震動。\n" NOR) ;
        if (random(5) > 2)
        {
                ob->move (__DIR__"ice1") ;
                tell_object(ob , BLU
"你被拋在冰山之上，船底撞破的洞孔甚大，只一頓飯時分便已
沉得無影無蹤。\n" NOR);
        }
        else
        {
                tell_object(ob , HIY "你被撞得暈了過去......\n" NOR);
                ob->unconcious();
                ob->move ("/d/beijing/haigang");
        }
}