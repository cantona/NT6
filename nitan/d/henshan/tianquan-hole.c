#include <ansi.h>
inherit ROOM;

string look_bi(object me);

void create()
{
        set("short","天泉洞");
        set("long", @LONG
一進洞，便聽見了泉水（quanshui）流動的聲音，只見這口泉水
從洞中一角落處湧出來，旁邊卻立有一碑（bei）。 山洞正前是個大
石壁（bi），壁上刻有圖畫，石壁旁卻插有一把木劍（mu jian）， 
像是有人曾經在這裏練過劍。山洞西面是一張石牀（bed），由此斷定
曾經有人在這裏住過。
LONG );

        set("exits",([
              "out":__DIR__"xuanyadi",
        ]));

        set("item_desc",([
              "mu jian":"\n一把木劍深深地插在石壁中，直至劍柄，可見當初插劍之人功力何等深厚，實屬罕見。\n",
              "bed":"\n一張非常粗陋的石牀，上面卻沾滿了灰塵。\n",
              "quanshui":"\n一股清泉源源地從底下湧出，水質清澈，令人忍不住想喝(he)上兩口。\n",
              "bei":"\n上書："HIR"天 泉 之 水"NOR" 字峯遒勁有力。\n",
              "bi":( : look_bi :),
        ]));


        setup();

}

void init()
{
        add_action("do_he","he");
        add_action("do_xue","xue");
        add_action("do_ba","ba");

}

string look_bi(object me)
{
        string msg;        
        int furong,zigai;

        me=this_player();
        furong=me->query_skill("furong-jianfa",1);
        zigai=me->query_skill("zigai-jianfa",1);

        msg=HIC"\n你仔細一看，石壁上刻着五個手持長劍的小人，每人各使一招，細看下像是一套劍法。\n"NOR;

        if(zigai&&furong)msg+=HIY"你仔細琢磨，隱約覺得這套劍法像是[紫蓋劍法]和[芙蓉劍法]的招式。\n"NOR;
        if(zigai&&!furong)msg+=HIY"你仔細琢磨，隱約覺得這套劍法像是有[紫蓋劍法]的招式。\n"NOR;
        if(!zigai&&furong)msg+=HIY"你仔細琢磨，隱約覺得這套劍法像是有[芙蓉劍法]的招式。\n"NOR;
        msg+=HIC"你越看越起勁，忍不住想跟着學(xue)起來。\n"NOR;
        
        write(msg);
                
        write(@TEXT

  ●>              ●           ●             \  ●                   ●
  \ __           --v|\        \//>---           \//\            --v|^ 
  /<               /<         //>                   <\              /<          
                                                                        
[天柱雲氣]    [泉鳴芙蓉]    [鶴翔紫蓋]        [雁回祝融]       [石磬鐘聲]
                                                                     
TEXT         
);


        return "";

}

int do_he(string arg)
{
        object me=this_player();
        
        if(!arg||arg!="quanshui")
                return notify_fail("你想喝什麼？\n");

        if(me->is_fighting()||me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
       
        if( query("D_TIANQUAN", me) )
                return notify_fail("你已經喝過天泉水了。\n");
        
        addn("water", 200, me);
        write("你俯下身喝了一口泉水，只覺得泉水甘甜無比，平生從未嘗過。\n");

        set("D_TIANQUAN", 1, me);
        
        return 1;
}

int do_xue(string arg)
{
        object me=this_player();
        int furong,zigai,hengshan,cost_qi,cost_neili,cost_jing,lvl_add;
        
        furong=me->query_skill("furong-jianfa",1);
        zigai=me->query_skill("zigai-jianfa",1);
        hengshan=me->query_skill("hengshan-jianfa",1);
        cost_qi=25;
        cost_neili=25;
        cost_jing=10;
        lvl_add=(int)( (me->query_skill("sword",1)+me->query_skill("literate",1))/2);


        if(!arg||(arg!="bi"&&arg!="石壁") )return 0;

        if(me->is_fighting()||me->is_busy())
        {
        write("你現在正忙着呢。\n");
        return 1;
        }
                
        if(!zigai||!furong||!hengshan)
        {
        write("石壁上的劍法像是幾種劍法融合在一起的，你看來看去，不知所措。\n");
        return 1;
        }

        if(zigai<100||furong<120||hengshan<120)
        {
        write("石壁上的劍法你似乎學過一點，但是還是不能融會貫通。\n");        
        return 1;
        }

        if(me->query_skill("literate",1)<300)
        {
        write("也許是你的悟性太差，雖然學過上面的劍法，但還是將其不能融會貫通。\n");
        return 1;
        }

        if( query("max_neili", me)<5000 )
        {
        write("你的內力修為太差，無法練習石壁上的劍法。\n");
        return 1;
        }

        if(me->query_skill("sword",1)<=me->query_skill("hsws-sword",1))
        {
        write("你的基礎太差了，石壁上的劍法只能學到這個程度。\n");
        return 1;
        }

        if( query("jing", me) <= cost_jing )
        {
        write("你的精力無法集中。\n");
        return 1;
        }

        if( query("neili", me) <= cost_neili )
        {
        write("你的內力不足，無法繼續練習。\n");
        return 1;
        }        

        if( query("qi", me) <= cost_qi+5 )
        {
        write("你的體力不足，無法繼續練習。\n");
        return 1;
        }
        
        if(me->query_skill("hsws-sword",1)>=120)
        {
        write("石壁上的劍法你已全部領悟，以後就靠自己勤加練習了。\n");
        return 1;
        }

        write("你以手作劍，將石壁上的劍法練習了一遍，覺得漸有所悟。\n");
        me->improve_skill("hsws-sword",lvl_add);
        me->receive_damage("qi",cost_qi);        
        me->receive_damage("jing",cost_jing);
        addn("neili", -cost_neili, me);

        return 1;

}


int do_ba(string arg)
{
        object me=this_player(),jian,here;

        if(!here = find_object(__DIR__"tianquan-hole"))here = load_object(__DIR__"tianquan-hole");
        
        if(!arg||(arg!="jian"&&arg!="mu jian"&&arg!="木劍"))
                return notify_fail("你要拔什麼？\n");
        
        if( query("neili", me)<5000 )
        {
        message_vision(HIG"$N用力想要將木劍從石壁中拔出來，但是木劍卻紋絲不動。\n"NOR,me);
        return 1;
        }                

        message_vision(HIG"唰~！的一聲，$N已將木劍從石壁中拔了出來。\n"NOR,me);

        jian=new(__DIR__"obj/mujian");
        jian->move(me);

        return 1;
}