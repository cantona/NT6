#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "「狐仙」" NOR, ({ "huxian book", "huxian", "book" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIM "一本破舊的書，也不知道這是誰寫的。沒"
                            "事可以看看(read)。\n" NOR);
                set("value", 50);
                set("material", "paper");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");

}

int do_read(string arg)
{
        if (arg == "huxian book" || arg == "huxian" || arg == "book")
        {
                set("lunhui-sword_quest/read_huxian_book", 1, this_player()); 
                return notify_fail(WHT "\n"
"---------------------------------------------------------\n\n"
"                       狐    仙\n\n"
"    衡陽城內有一條巷子，很偏僻，巷子深處，有個不大的小院。\n"
"人了院門，有幾間簡陋的草堂，這裡就是杜鳳鄂“百狐齋”了。\n\n"
"    古往畫人，寫飛禽走獸的不少。虎嘯山谷，馬躍平川，鶴唳\n"
"荷塘，雉伏草叢等等。但專畫狐的人不多。\n\n"
"    杜鳳鄂就專事狐畫。\n\n"
"    他想象奇特，用墨大膽，筆下畫有灰狐。白狐、赤狐、黑狐\n"
"藍狐、紫狐……或靜、或嬉、或怒、或媚，或狡黠、或機靈、或\n"
"嬌憨，千姿百態，形神兼具。\n\n"
"    他的畫中，或為主體，或力襯景，都少不了狐。\n\n"
"    如前人畫芭蕉，多以小鳥點綴，他的《芭蕉小景》卻畫兩只\n"
"狐玩耍于蕉下，就不一般了。再如他的《四美圖》亦每幅皆以狐\n"
"綴之，昭君圖的狐端莊，貂蟬圖的狐嫵媚，貴妃圖的狐雍容，西\n"
"施圖的狐嬌柔。人狐和諧統一，相得益彰，有一股空靈的氣韻。\n\n"
"    為了畫狐，杜鳳鄂便常伏在山野林中草垛屋後窺覷狐的行蹤。\n"
"狐類狡黠多疑、靈敏迅疾，常于夜間出沒，故爾他想觀狐實非易\n"
"事。\n\n"
"    有回他去山中，守了半天也沒見一只狐，只好悻悻而返。\n\n"
"    途中，他碰到一個獵人。獵人肩上挎一只狐。狐是獵人下夾\n"
"捕的，所以只傷未死。 他就將狐買了下來。 這是一只幼狐，紅\n"
"色的毛油光發亮，兩只小眼怯生生地望著他，他愛憐地摸了摸狐\n"
"的腦袋。\n\n"
"    回來，杜鳳鄂用鹽水細心地為幼狐擦洗傷口。經他悉心喂養\n"
"不幾天幼狐傷口就癒合了，小家伙在籠子裡躥上蹦下。\n\n"
"    杜鳳鄂常逗狐玩耍，畫了不少草圖。\n\n"
"    有次他作好一幅畫後，又出來逗那狐玩。\n\n"
"    他問：“你是公狐母狐？”狐說：“我是母狐。”他問：傳\n"
"聞狐能化人，此話當真？”狐說：“信則有，不信則無。”他又\n"
"說：“那你能不能變個美女？”狐說：“能又怎樣？”他說：嫁\n"
"給我。”狐道：“你將我放出籠來。”\n\n"
"    其實，他問這些的時候，紅狐並沒開口。但他想象狐就是這\n"
"麼和他說的。他真的將籠門打開，紅狐沒有變成美女，卻哧溜一\n"
"聲消失在夜色中。\n\n"
"    第二大晚上，他睡下後，被門外一陣蟋蟋□□聲吵醒了。他\n"
"開門一看，門外站著一大群狐。其中一只跑到他跟前，用爪子抓\n"
"他的褲管，用舌頭舔他的腳踝。他認出來了，正是他放走的那只\n"
"紅狐。\n\n"
"    一大群狐跑到院中打鬧嬉戲，追逐翻滾，至半夜才散。\n\n"
"    次日又是如此。\n\n"
"    杜鳳鄂明白了：狐是有靈性的生靈，那只被他放走的紅狐為\n"
"了報恩，領來一群狐讓他畫哩。\n\n"
"    從此，他的狐畫更出神入化了。\n\n"
"    盡管杜風鄂的狐畫畫得好，他仍然受窮。因為狐畫無人願買\n"
"──狐在民間是不吉的象征，誰願買不吉的東西掛在家裡呢？\n\n"
"    杜鳳鄂不管這些。\n\n"
"    這一天，他于街頭賣畫。走來一個女子，被那麼多栩栩如生\n"
"的狐畫吸引了，出高價買了兩幅。因為第一次有人買他的畫，且\n"
"是個女子，他不禁朝女子多看幾眼，只見她明眸流波，風姿婉媚，\n"
"只是不展笑顏，似花愁柳怨。女子被杜鳳鄂瞧得有些害羞，卷畫\n"
"匆匆離去。\n\n"
"    第二日，女子又來畫攤買走了他的兩幅畫。一連幾日，都是\n"
"如此。\n\n"
"    時間久了，杜鳳鄂漸漸覺得有點溪蹺，女子再次來時，他就\n"
"問：“小姐是何人家閨秀，緣何買那麼多畫？”女子卻笑而不答。\n"
"他說你不告訴我，這畫，我不賣了。女子說：“你這人真是好笑，\n"
"你賣畫，我出錢，且有不賣之理？”杜鳳鄂的□脾氣上來了，他\n"
"說你不告訴我，我就不賣。\n\n"
"    女子氣呼呼地走了。杜鳳鄂有些後悔。\n\n"
"    沒想到第二天那個女子卻找上門來。\n\n"
"    杜鳳鄂驚訝問：“我沒告訴你住址，你怎麼找到我家呢？”\n"
"女子一笑：“說出來只怕會嚇著你。”  杜鳳鄂說有什麼好怕的。\n"
"女子說：“實不相瞞，我是一個狐仙，很喜歡你的畫，所以常買\n"
"一兩幅回去賞玩。沒想到你這人很怪，在街頭刨根問底，叫我怎\n"
"麼回答呢？”又說：“你超凡脫俗，對狐的一片痴情，世間能有\n"
"幾人知？只有我們狐能了解啊！”兩人敘談了好些時候。臨走時\n"
"女子又送給杜鳳鄂好些銀兩，杜鳳鄂推辭不接。女子說：“我懂\n"
"些法術，這些錢來得容易，你收下無妨。”\n\n"
"    杜鳳鄂也就接了。此後，狐仙常來“百狐齋”小坐。還幫杜\n"
"鳳鄂理案磨墨，兩人相處得很是融洽。\n\n"
"    一日，杜鳳鄂在街頭賣畫，聽市人議論，今日縣衙要宣斬一\n"
"個青樓女子。原來，縣令的兒子到“千香閣”撒野，被一個青樓\n"
"女子殺了。這個惡少平時橫行泅州，作惡多端，多少人敢怒不敢\n"
"言。沒想到一個青樓女子為民除了害。人們都欽佩這個女子的剛\n"
"烈，同時也恨蒼天的不公。\n\n"
"    刑場上人頭攢動。杜風鄂也在人流中觀望。當囚車駛向刑場\n"
"的時候，杜鳳鄂的心一下子揪緊了：這女子不是狐仙嗎？他心急\n"
"如焚。但想到她是狐仙，也許會使妖術逃生，杜鳳鄂的心裡又略\n"
"略有些寬慰。\n\n"
"    行刑令下，劊子手飛刀而下，鮮血四濺。狐仙頭身兩離，栽\n"
"倒在地。\n\n"
"    人流散後，杜鳳鄂奔向屍體，摸著冰涼的肢體，也不知狐仙\n"
"的真身有沒有逃走，不禁黯然神傷。\n\n"
"    一個在一旁哭泣的女子抬起頭問杜鳳鄂：“你就是杜才子吧？\n"
"”杜鳳鄂說：“正是。”女子說：“我聽緋胭姐提起過你，”杜\n"
"鳳鄂問：“她叫緋胭？你是她什麼人？她是否真的是狐仙？”女\n"
"子悲嚥道：“她哪是什麼狐仙？ 她和我一樣， 都是窮人家女子，\n"
"被縣令惡子相逼才落人風塵的。緋胭姐很喜歡你的畫，羨慕你的\n"
"才氣，得知你日子清苦，就想幫幫你，又不便說出真相，才和你\n"
"開玩笑說她是狐仙的……”\n\n"
"    杜鳳鄂抱住緋胭的屍體好久才哭出聲來。\n\n"
"---------------------------------------------------------\n"
"\n\n" NOR);
}
}
