# TODO: Make it work automatically

commits = ["830043acd7a075fdfc690f09e31af19ed0869156",
"046ecedc3b675ab74c71364d509c21620645aa02",
"859ae57eaa93480ce4b56cb3e28d806df8887f2b",
"06511a85e4a1903ca27d9617e83c8bb62a2b5a7d",
"06056f0aac18e666d924fb1af501ec7f03472530",
"855288b87e58bdcebcfba1daabe702d1ba90c6af",
"89cb374d4795c17b4343ad8f8344b8b966007382",
"0af7d49a561dea5db9b6dcef28f8ed4e484b03e2",
"09284502bfc3760c2e6abf828dcf9b9867a16e67",
"0c9c48ba728637ca0b2f43f1f124857f38a7b174",
"890f9d553483f85a1a109624594eefd2e6a3fdd1",
"0ffc8e39299758927fb2f0dc02c49870036a132c",
"100e632f732582f452726741f096a8d35b89a176",
"94e0b25e8c9b19c83734bf1f88a702fccb973730",
"9447a9d0e9fd6f4f61239df7fbaf7733b91d71fb",
"972214ec4f98b192a1956ab9ec087ea153b990fb",
"1ad3b7a07b6e366b6a215bce318b962be9b36e96",
"1a95c5d93fb9f6f00656547798e39d80239be443",
"a0adae2aee890f92473eb56808e48489e815bb6a",
"a2eee0185241f545981fe38c0729e6dec9c3acdc",
"a363cb59fc0b830466423b319180a86f377249bf",
"2950b2b004dde9db354ce0cf071f5ab5622fe34c",
"ab8502760339ed2eabf008f437b80b2a5e3bd7e6",
"2c798f69f98ef62ff0be00cb52582ea1d7d2f9bf",
"adb4ec9ab3731b4d821aee5b513fe054408924f1",
"2c6cc26d5e0b5f652e1ca789a2724fd1e04c6240",
"ab1ecd4b0c5a05a0920f869d61d45157fc46e5f4",
"ab7b7d530bf697081263db7b4bc0cf8fecb7bcf9",
"2d031d127029eeca456f1bd16e5ee80b1578c1bd",
"32809e6c045440c9a1f619edfbf0ab0ac88c63f6",
"b7e9766719f07c640704d51aced9899cfa7f3201",
"37ac399befbb68d8a2ff1a383d60fbcc4d424637",
"b9218845284b2be4921de9a3d043e523a7e7bec1",
"3bd31869612426e03d24a09e5999024102ed16bd",
"3d6a256bca22f253c5740468322df7f1c6cc4b40",
"3f4e8dc0e53f1d31924951112e437b9024b6261a",
"41946b3c817f24b5558bd5c77cc45b33b00440dc",
"c474fe88f1db282c63ffdd7518d75dc3a9b31a3f",
"c7b12601b17651a93ffe3e3a8b157fc34e07ca5d",
"48d5e70389e4dfa822f69df9d067a013b8056653",
"4e081039a146e67d3b499b62335795b285d3d065",
"d25923853ee30304b576eb9ae444855b55baa659",
"d5d2e5798d76b6ba83db4a3ee152dffa10e471b9",
"5732adbea3b816ed4d082b9e2f231ffe83c09709",
"dc8ec042b88a1c7ccad3b187f0d5982595a3a9da",
"5c5ed9a3bfcdf647c79adb8a204bfa43fb6ff580",
"dfa5e02cab5a3891c45da5a41b4f6b368dd0d0f7",
"e189eecd645cd0af1b6ac5c1f43482c98a85389a",
"e3753eb605fc8cb63ab9b9120735807ba5a0d4d9",
"64e398a995604fbc0391ef6806df9c332c243ef5",
"6425174092db72e914b50ea553374d065db2a372",
"e69de29bb2d1d6434b8b29ae775ad8c2e48c5391",
"ea2484d6ae6639cf0f7e7b34e130f593769b0da2",
"f14ff13712b87bf5462ecd34e207b79a967afad8",
"76c6ee7b096f45fb286e310f79ca01b68cc66a49",
"f9fd737fb5c4101bc466cad9dee41de432b86916",
"fd8490bccc04447fc4893364f09ba68513709ecd"]

from subprocess import call
filename = "file"
i = 1
for c in commits:
	f = open(filename + str(i), "wb")
	call(["git", "show", c], stdout=f)
	i += 1