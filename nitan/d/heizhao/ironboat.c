// Room: /heizhao/ironboat.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "鐵舟");
        set("long", @LONG
這是一艘黑黝黝的小船，舟中放著兩柄鐵槳，鐵舟很小至多只
能乘坐二人。
LONG );
        set("outdoors", "taoyuan");
        set("resource/water", 1);
        set("exits", ([
                "south" : __DIR__"xiaowu",
                "out"   : __DIR__"pububian",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1250);
        set("coor/z", 20);
        setup();
}

void init()
{
        object ob = this_player();
        if( query("max_neili", ob)>1500 )
        {
                call_out("upload", 1, ob);
        }
        else
        {
                message_vision(HIR"\n你內力不足，強行解纜非被沖到了邊緣
之外，一瀉如注，非摔得粉身碎骨不可！\n"NOR, ob);

        }
}

void upload( object ob )
{
        message_vision( BLU
"\n$N舉起鐵舟，喝一聲：“起！”用力擲入瀑布的上遊。鐵舟
一經擲出，$N立即搶起鐵槳，挾在左腋之下，只見鐵舟已順
著水流沖到跟前，湧身前躍，落入舟中。\n\n" NOR, ob);
        ob ->move(__DIR__"ironboat2") ;
        message_vision( HIG
"\n這時水聲轟轟，眼見鐵舟隨著瀑布即將流至山石邊緣，$N左
手鐵槳急忙揮出，用力一扳，鐵舟登時逆行了數尺。
鐵槳再是一扳，那舟又向上逆行了數尺。雙膀使力，揮槳與
激流相抗。那鐵舟翹起了頭鼓浪逆行。\n\n" NOR, ob);
        call_out("upload2", 10, ob);
}
void upload2( object ob )
{
        message_vision( HIC
"\n此處水流雖不如瀑布般猛沖而下，卻也極是急促，$N劃得面
紅氣促，好幾次險些給水沖得倒退下去。"
"\n鐵舟向右首轉過山角，眼前已非瀑布，乃是一道急流，$N扳
動鐵槳，在急湍中逆流而上。\n\n" NOR, ob);
        message_vision( HIG
"\n又行一陣，劃過兩個急灘，一轉彎，眼前景色如畫，清溪潺
潺，水流平穩之極，幾似定住不動。那溪水寬約丈許，兩旁
垂柳拂水，綠柳之間夾植著無數桃樹，若在春日桃花盛開之
時，想見一片錦繡，繁華耀眼。這時雖無桃花，但水邊生滿
一叢叢白色小花，芳香馥鬱。\n\n" NOR, ob);
        call_out("upload3", 10, ob);
}
void upload3( object ob )
{
        message_vision( HIG 
"\n$N直瞧得心曠神怡，料想不到這高山之巔竟然別有一番天地。
溪水碧綠如玉，深難見底，溪面水平如鏡，底下卻有一股無
聲的激流。
\n那鐵舟緩緩向前駛去，綠柳叢間時有飛鳥鳴囀。鐵舟忽然鑽
入了一個山洞。洞中香氣更濃，水流卻又湍急，只聽得一陣
眼前鬥亮，鐵舟已然出洞，洞外是個極大的噴泉，高達二丈
有余，奔雪濺玉，一條巨大的水柱從石孔中直噴上來，飛入
半空，嗤嗤之聲就是從噴泉發出。那溪水至此而止，這噴泉
顯是下面溪水與瀑布的源頭了。\n"NOR, ob);
        call_out("upload4", 10, ob);
}
void upload4( object ob )
{
        message_vision( HIR 
"\n$N起身上岸，將鐵舟拉起放在石上，回過頭來，卻見水柱在
太陽照耀下映出一條眩目奇麗的彩虹。\n\n" NOR, ob) ;
        ob->move (__DIR__"shanlu10");
}