// laocai.c

inherit NPC;
string inquiry_dao();

void create()
{
        set_name("老材", ({ "lao cai","cai" }) );
        set("gender", "男性" );
        set("nickname","老財");
        set("age", 40);
        set("long", "一個有名的吝嗇鬼，好象他整日看守著柴房也能發財似的。\n");
        set("shen_type",-1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 18);
        set("con", 18);
        set("int", 18);
        set("attitude", "friendly");
        set("inquiry" , ([
        "柴刀" : (: inquiry_dao :),
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

string inquiry_dao()
{
 object me=this_player();
 object ob;

if (present("chai dao",me))
  return "老材瞪著眼說：你身上帶著一把，還想要！\n";
 else
 {
 ob=new("/d/baituo/obj/chaidao");
 ob->move(me);
  return "老材遞給你一把柴刀，囑咐道說：小心保管！\n";
 }
}