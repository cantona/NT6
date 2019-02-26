//jianglishi 泥潭獎勵使
//smallbear 03.10.26

#include <ansi.h>

inherit NPC;

mixed ask_gongxian();
mixed ask_jiangli();
int do_lingqu(string arg);

void create()
{
        set_name("獎勵使", ({ "jiangli shi", "shi", "jiangli" }));
        set("nickname", HIY "泥潭" NOR);
        set("long", "他就是泥潭獎勵使，如果你對泥潭有貢獻的話，可以到他這裏領取獎勵。\n");
        set("gender", "男性");
        set("age", 20);
        set("per", 30);
        set("attitude", "peaceful");
        set("inquiry", ([
                "貢獻度"   : (: ask_gongxian :),
                "獎勵" : (: ask_jiangli :),
        ]));

        setup();
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/xianlv")->wear();
}

void init()
{
        add_action("do_lingqu", "lingqu");
}


mixed ask_gongxian()
{
        object me;
         int gx;

        me = this_player();
         gx=query("hx_gongxian", me);

        if( !query("hx_gongxian", me) )
                return "“你好像還沒有為泥潭作出貢獻哦，要加油。”";

        if( query("hx_gongxian", me)>0 )
                  write (WHT"獎勵使對你笑了笑，説道：“幹得好！你現在已經有"+chinese_number(gx)+"點貢獻度了，要繼續努力哦。”\n"NOR);
        return 1;
}

mixed ask_jiangli()
{
         object me;

         me = this_player();
        
        if( !query("hx_gongxian", me) )
                return "“你還沒有貢獻度呢，就來問獎勵？”";

        if( query("hx_gongxian", me)>0 )
                return "“你是來拿獎勵的嗎？看一下 help gongxian，然後找我領取吧。”";

         return 1;
}

int do_lingqu(string arg)
{
         object me,ptz,bts,bcs,xd,slw,xsd,hhxd,txyl,jzjd,xhd,mn,fc,zs,sj;
         me = this_player();

        if( !query("hx_gongxian", me) )
                return notify_fail("你目前沒有貢獻度，不能領取獎勵。\n");

         if ( ! arg || arg == "" )
                return notify_fail("你想領取什麼呢？\n");

         if ( arg != "菩提子" && arg != "補天石" && arg != "冰蠶絲" && arg != "仙丹" && arg != "神力丸"
&& arg != "洗髓丹" && arg != "火紅仙丹" && arg != "天香玉露" && arg != "九轉金丹" && arg != "玄黃紫清丹"
&& arg != "瑪瑙殘片" && arg != "翡翠殘片" && arg != "鑽石殘片" && arg != "水晶殘片" )
                return notify_fail("獎勵使看了你一眼：“我這裏可沒有你想要的，決定了再來找我吧。”\n");

         if ( arg == "補天石")
                 {
                         if( query("hx_gongxian", me)<1 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");
                        
                         write(WHT"獎勵使微微點了點頭，拿出一塊補天石交了給你。\n"NOR); 
                                    addn("hx_gongxian", -1, me);
                                    bts = new("/d/item/obj/butian"); 
                                    bts->move(this_player());
                                    return 1;
                         
                 }

         if ( arg == "冰蠶絲")
                 {
                         if( query("hx_gongxian", me)<1 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一束冰蠶絲交了給你。\n"NOR); 
                                    addn("hx_gongxian", -1, me);
                                    bcs = new("/d/item/obj/tiancs"); 
                                    bcs->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "菩提子")
                 {
                         if( query("hx_gongxian", me)<2 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆菩提子交了給你。\n"NOR); 
                                    addn("hx_gongxian", -2, me);
                                    ptz = new("/d/shaolin/obj/puti-zi"); 
                                    ptz->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "仙丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆仙丹交了給你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    xd = new("/clone/gift/xiandan"); 
                                    xd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "神力丸")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆神力丸交了給你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    slw = new("/clone/gift/shenliwan"); 
                                    slw->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "洗髓丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆洗髓丹交了給你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    xsd = new("/clone/gift/xisuidan"); 
                                    xsd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "火紅仙丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆火紅仙丹交了給你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    hhxd = new("/clone/gift/unknowdan"); 
                                    hhxd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "天香玉露")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一滴天香玉露交了給你。\n"NOR); 
                                    addn("hx_gongxian", -3, me);
                                    txyl = new("/clone/gift/tianxiang"); 
                                    txyl->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "九轉金丹")
                 {
                         if( query("hx_gongxian", me)<6 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆九轉金丹交了給你。\n"NOR); 
                                    addn("hx_gongxian", -6, me);
                                    jzjd = new("/clone/gift/jiuzhuan"); 
                                    jzjd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "瑪瑙殘片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一片瑪瑙殘片交了給你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    mn = new("/clone/gift/cagate"); 
                                    mn->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "翡翠殘片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一片翡翠殘片交了給你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    fc = new("/clone/gift/cjade"); 
                                    fc->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "鑽石殘片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一片鑽石殘片交了給你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    zs = new("/clone/gift/cdiamond"); 
                                    zs->move(this_player());
                                    return 1;
                }
                 
         if ( arg == "水晶殘片")
                {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");
                         write(WHT"獎勵使微微點了點頭，拿出一片水晶殘片交了給你。\n"NOR);
                                    addn("hx_gongxian", -8, me);
                                    sj = new("/clone/gift/ccrystal");
                                    sj->move(this_player());
                                    return 1;
                }
                               
         if ( arg == "玄黃紫清丹")
                {
                         if( query("hx_gongxian", me)<10 )
                                  return notify_fail("你的貢獻度不夠了，再多多努力吧。\n");

                         write(WHT"獎勵使微微點了點頭，拿出一顆玄黃紫清丹交了給你。\n"NOR);
                                    addn("hx_gongxian", -10, me);
                                    xhd = new("/clone/gift/xuanhuang");
                                    xhd->move(this_player());
                                    return 1;
                }
                return 1;
}