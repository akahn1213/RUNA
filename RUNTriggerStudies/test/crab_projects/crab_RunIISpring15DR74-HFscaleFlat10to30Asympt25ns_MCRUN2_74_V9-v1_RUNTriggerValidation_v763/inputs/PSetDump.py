import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/620/00000/D4BD3FF3-1D40-E511-8375-02163E0142EE.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/808/00000/3E6025B5-7340-E511-A8B7-02163E01440E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/809/00000/FED49B77-7440-E511-ACA4-02163E015603.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/888/00000/823ED736-0941-E511-B9BA-02163E0145D8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/890/00000/BE9881D7-2741-E511-B9E9-02163E015539.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/901/00000/FC888C66-2841-E511-820F-02163E014531.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/943/00000/362CA705-3741-E511-ACD6-02163E0144DB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/944/00000/E020E2B8-5941-E511-9975-02163E013414.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/948/00000/B2E1FF3E-4141-E511-B07E-02163E014260.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/950/00000/7E834373-4241-E511-9A88-02163E015661.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/952/00000/04EE219A-4241-E511-AA9A-02163E0140E9.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/253/954/00000/2474BC92-4541-E511-A5B3-02163E011D5A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/094/00000/F45A9408-0546-E511-8705-02163E01299C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/096/00000/86B9F7D7-6445-E511-B0BA-02163E012AAF.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/109/00000/5A80457C-AF45-E511-8151-02163E014511.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/210/00000/242761FD-3746-E511-8C8E-02163E014599.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/212/00000/AA01BCA8-0346-E511-9F44-02163E012A4C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/219/00000/E8F0A204-E945-E511-A065-02163E01385B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/226/00000/04858F5C-CC45-E511-8F6E-02163E0137E9.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/227/00000/1AB8CD26-CB45-E511-AAC1-02163E014400.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/227/00000/285EAB2B-CB45-E511-9485-02163E013640.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/227/00000/8473F925-CB45-E511-8C39-02163E008EB2.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/227/00000/A8C2742D-CB45-E511-A976-02163E01395A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/227/00000/F6A0332E-CB45-E511-B89A-02163E0133DE.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/229/00000/9EB5D2FD-A945-E511-A53D-02163E01478D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/231/00000/307AC4A2-2046-E511-B367-02163E0119E0.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/232/00000/14C82CF2-B945-E511-8C29-02163E011A4C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/232/00000/727607F7-B945-E511-8C6B-02163E011C53.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/232/00000/B40823DA-B945-E511-AB30-02163E011D96.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/280/00000/5E61AEB8-2E46-E511-8A8B-02163E013727.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/282/00000/5C772A8E-0A46-E511-A665-02163E014463.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/283/00000/36F8E510-C745-E511-AE5A-02163E01449E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/284/00000/524E04C5-6945-E511-B12C-02163E0145F6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/285/00000/148BA1F5-E245-E511-A781-02163E014258.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/289/00000/8E00C316-9345-E511-B344-02163E01259D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/290/00000/2E4407B8-C445-E511-8C48-02163E01469A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/292/00000/28382C49-D545-E511-98B0-02163E014794.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/292/00000/8A414E4D-D545-E511-B684-02163E014187.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/1C7A702E-1646-E511-B41F-02163E01475A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/2C85892C-1646-E511-885E-02163E013695.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/363C5423-1646-E511-BE9E-02163E014506.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/446F2723-1646-E511-B23B-02163E011D18.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/627C3625-1646-E511-A3D7-02163E0146EC.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/64F24421-1646-E511-AA6C-02163E014573.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/9E9E2523-1646-E511-8459-02163E013529.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/293/00000/CEC64C26-1646-E511-8410-02163E013699.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/294/00000/50433A0B-EB45-E511-803F-02163E0119FB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/294/00000/8A15560B-EB45-E511-859D-02163E0119FB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/294/00000/D2DDC805-EB45-E511-87F9-02163E0144BD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/306/00000/7A41FBCF-C945-E511-B10B-02163E011A62.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/307/00000/049B4675-9B45-E511-9E93-02163E01443C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/308/00000/20B77015-E945-E511-9C6A-02163E012A4C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/309/00000/30223451-9C45-E511-A886-02163E014752.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/313/00000/7E2967B5-2C46-E511-9BCE-02163E013932.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/314/00000/B69E0B62-D445-E511-9656-02163E013794.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/315/00000/C81A7AD3-8445-E511-A257-02163E014328.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/317/00000/325EFE4E-8245-E511-AF7C-02163E0144A6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/318/00000/AC655E7F-9D45-E511-B666-02163E011C6D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/52957EB0-F845-E511-B1FE-02163E0135AD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/64A57FAB-F845-E511-9487-02163E013561.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/8034B8AE-F845-E511-9F73-02163E01459B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/8652B3AD-F845-E511-A965-02163E01358E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/A24E98AB-F845-E511-903B-02163E014416.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/319/00000/DE3221AD-F845-E511-9C56-02163E0141DB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/207FFE04-CB46-E511-9FF4-02163E01364C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/224984D9-D146-E511-B163-02163E014430.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/2855704C-C546-E511-A6E7-02163E011DB6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/28AEF6BE-CD46-E511-AF52-02163E011F87.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/2C8B94A7-C546-E511-A259-02163E0134E8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/3441F2EB-C946-E511-949E-02163E0144A6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/365C3342-C546-E511-BE2A-02163E0144A6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/7E815AE5-C446-E511-818B-02163E012755.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/8203CCE8-C446-E511-8A73-02163E011DB6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/983FBEC0-C646-E511-A1EE-02163E0133EC.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/9884D0A3-C846-E511-9F37-02163E0133B5.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/A4AD85A3-C546-E511-AF18-02163E01364C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/AC7F74E5-C946-E511-B816-02163E012838.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/BA7E8D72-BC46-E511-A287-02163E0144AE.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/BC7947B4-CD46-E511-840D-02163E0143DD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/C8B8B20F-CB46-E511-A4DC-02163E015541.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/F0C4DBC0-C646-E511-8A36-02163E0133EC.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/332/00000/FABCB79F-C846-E511-A671-02163E01432F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/340/00000/28AAEAB1-A045-E511-93CA-02163E0143D2.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/341/00000/BC6A8A57-E345-E511-A23F-02163E01389C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/341/00000/C45A9149-E345-E511-99FB-02163E011862.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/342/00000/046A9EF8-9645-E511-A364-02163E011B33.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/342/00000/6CC8152E-9745-E511-B966-02163E014576.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/342/00000/760133F1-9645-E511-A42A-02163E014474.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/4008D4A8-E545-E511-9EE1-02163E0145BB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/42608499-E545-E511-BD44-02163E01299C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/78518A94-E545-E511-8ED7-02163E011EA2.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/C2960E9F-E545-E511-BE50-02163E011826.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/C8D6B89A-E545-E511-B4AA-02163E013695.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/EAF3F0A0-E545-E511-9139-02163E011C7F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/349/00000/EE402B98-E545-E511-9260-02163E013917.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/362/00000/98BF9A3C-4446-E511-A309-02163E0146C8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/0CFC25F0-C246-E511-8848-02163E012755.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/0E10C5EA-C246-E511-9740-02163E01412F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/14555FEC-C246-E511-A6E5-02163E013858.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/28F7F107-C346-E511-B900-02163E0127B5.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/2CF065EC-C246-E511-91B4-02163E01340A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/44E074EE-C246-E511-9593-02163E012560.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/4CCC31ED-C246-E511-8916-02163E0141F2.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/547C0DEB-C246-E511-AF1E-02163E014414.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/6019BC96-C446-E511-95CE-02163E014631.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/74FF71ED-C246-E511-BABA-02163E0134E8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/7E80DBFD-C246-E511-A078-02163E0143E3.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/AAB4D9EA-C246-E511-9C4C-02163E014717.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/B83BDE05-C346-E511-A3C3-02163E0133B8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/BA9FB1EA-C246-E511-9932-02163E01364C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/C24BC0FF-C246-E511-A955-02163E011F87.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/D83208ED-C246-E511-8668-02163E012003.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/DA8A8BEC-C246-E511-8F02-02163E013529.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/FA07A706-C346-E511-BBB1-02163E013591.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/380/00000/FCD1CFEE-C246-E511-A113-02163E013917.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/416/00000/CE9EF6CA-8546-E511-9816-02163E0118D1.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/437/00000/4442DAE8-8846-E511-93BB-02163E01378A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/437/00000/625FC2E8-8846-E511-8C89-02163E011DB6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/437/00000/6A9C69E8-8846-E511-BA81-02163E011E8F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/450/00000/3099B067-9146-E511-AA7A-02163E01374E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/451/00000/E44C1DB5-9246-E511-8479-02163E012838.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/453/00000/3EAD6141-9446-E511-8FF3-02163E01432F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/454/00000/D63C8671-9546-E511-92E3-02163E01389F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/456/00000/82DA7E38-9646-E511-9804-02163E014243.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/457/00000/4067CD6C-9646-E511-BCE6-02163E012790.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/458/00000/02E8A3F3-9646-E511-844F-02163E011ED0.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/458/00000/CA50CCEA-9646-E511-A192-02163E01340A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/3E517229-5B47-E511-A8B8-02163E014652.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/42E2332D-5B47-E511-97D1-02163E01396F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/62AB8529-5B47-E511-A3D8-02163E01353A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/66A1D525-5B47-E511-A813-02163E0141FF.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/8C1FB128-5B47-E511-BDAB-02163E011E5B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/A64FF52B-5B47-E511-B8A8-02163E015603.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/A8EC1B2A-5B47-E511-AC40-02163E01298B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/C2E5C229-5B47-E511-BA33-02163E0146C8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/CE919729-5B47-E511-8510-02163E0133C6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/E2A26248-5B47-E511-BFA1-02163E0142E1.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/459/00000/F6947831-5B47-E511-81BE-02163E01374D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/500/00000/F6B2D7F2-D146-E511-8B07-02163E0121F3.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/511/00000/6046F4D2-D246-E511-B8C5-02163E0121F3.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/512/00000/1A4AA469-3247-E511-8CF7-02163E0136FD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/513/00000/746174E8-D146-E511-A630-02163E014717.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/530/00000/26E9768D-1847-E511-9A6A-02163E014414.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/532/00000/30544585-6E47-E511-B58D-02163E01477D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/532/00000/584CED85-6E47-E511-90CF-02163E014488.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/532/00000/682E2183-6E47-E511-8FF4-02163E01353A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/532/00000/9A0F4281-6E47-E511-9F05-02163E0140F0.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/532/00000/B6C5B883-6E47-E511-9A64-02163E01416A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/592/00000/EC572DCA-7247-E511-B074-02163E0155B9.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/602/00000/8CCCB889-C247-E511-BF8A-02163E014752.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/607/00000/92203FAB-BB47-E511-8A8D-02163E0141ED.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/0232E91A-7449-E511-94F1-02163E01427B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/16B28355-7449-E511-B3C1-02163E01412A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/28E22F9E-7449-E511-9AE4-02163E013917.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/34BEC71E-7449-E511-9C4E-02163E014309.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/842E5D7D-7449-E511-9BAC-02163E011A41.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/92990AFC-7449-E511-9180-02163E011A3A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/A4F0C924-7449-E511-90C3-02163E0142BF.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/BC176B58-7449-E511-8348-02163E01391B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/E22E4811-7449-E511-B6FC-02163E01229A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/E8DB800C-7449-E511-A592-02163E013865.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/608/00000/E8E1F8FB-7449-E511-A94D-02163E011A3A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/768/00000/4EC8AB25-1049-E511-B13F-02163E014342.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/780/00000/648F605B-2A49-E511-B3C4-02163E01340A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/785/00000/D8C832E1-3D49-E511-AE9B-02163E01229A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/06947E9F-204A-E511-B627-02163E0137BA.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/18D18896-204A-E511-B82D-02163E01190D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/260A1195-204A-E511-8627-02163E014125.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/6A03E597-204A-E511-B2EA-02163E01418B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/7086989C-204A-E511-B943-02163E013409.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/7CA25D9B-204A-E511-BF7A-02163E011955.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/823FA0A1-204A-E511-887F-02163E01453E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/AA29DAA0-204A-E511-83FD-02163E0136D5.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/BA4041A9-204A-E511-937D-02163E011E1D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/BE8974AB-204A-E511-9AB8-02163E01266D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/C42C66A7-204A-E511-A53D-02163E01448C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/F2098695-204A-E511-85CE-02163E014657.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/790/00000/F60BE6A7-204A-E511-AF26-02163E0146B3.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/824/00000/E62D22BA-5B4A-E511-B10E-02163E011D72.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/00CCC623-2B4B-E511-9B43-02163E011C3B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/06AB2A26-2B4B-E511-B79F-02163E01466E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/08FD401B-2B4B-E511-B095-02163E0133CA.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/22704723-2B4B-E511-877F-02163E013416.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/243C6E1F-2B4B-E511-91A7-02163E0120EE.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/2442756C-2B4B-E511-8DC1-02163E0145BB.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/325DAC2A-2B4B-E511-B983-02163E0124BD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/38C6B624-2B4B-E511-AAF2-02163E011845.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/3A75C03C-2B4B-E511-BDBB-02163E01205A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/42E5CF64-2B4B-E511-8664-02163E0138B1.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/44C0D81F-2B4B-E511-8C4B-02163E014335.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/46459324-2B4B-E511-8862-02163E012275.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/500AB82B-2B4B-E511-AD76-02163E01386C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/5425A727-2B4B-E511-BD50-02163E011E5E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/604DB053-2B4B-E511-871F-02163E01464F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/78E1AC23-2B4B-E511-81D2-02163E011EB6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/7A23072B-2B4B-E511-B7F0-02163E0145AA.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/7C05B020-2B4B-E511-A416-02163E011C2D.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/7E18E91D-2B4B-E511-AB6F-02163E0142B8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/7E25EC5D-2B4B-E511-8553-02163E013813.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/86F4DC1D-2B4B-E511-A6A4-02163E01369A.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/88C0CB1F-2B4B-E511-90E3-02163E0135D4.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/A06BD322-2B4B-E511-912D-02163E01460C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/A2CB5539-2B4B-E511-BDFD-02163E0133F6.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/A8EE1C2B-2B4B-E511-AE7C-02163E01426B.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/AE2F182A-2B4B-E511-8484-02163E01282E.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/B2895025-2B4B-E511-9695-02163E0134A3.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/BA24852A-2B4B-E511-9254-02163E0140F4.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/CC207D24-2B4B-E511-ACD8-02163E013578.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/D069862D-2B4B-E511-B11F-02163E014361.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/E4231A3A-2B4B-E511-AB61-02163E0145D8.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/833/00000/FCBEF924-2B4B-E511-9898-02163E0144AA.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/852/00000/E6A6D3CA-974B-E511-99CF-02163E0143D7.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/879/00000/A04F3AB0-9D4B-E511-A841-02163E01389C.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/879/00000/DEEDAFB8-9D4B-E511-BEF3-02163E0146CA.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/905/00000/168E44B3-B34B-E511-A04B-02163E013790.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/905/00000/22E454AF-B34B-E511-A0FF-02163E0146A1.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/905/00000/9A6078B5-B34B-E511-BC0C-02163E011CEF.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/906/00000/E4FF7026-DE4B-E511-9A88-02163E011F5F.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/907/00000/C2BBAC63-F84B-E511-B550-02163E0136D4.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/913/00000/0EE42CF9-EB4B-E511-AED1-02163E0142AD.root', 
        '/store/data/Run2015C/JetHT/MINIAOD/PromptReco-v1/000/254/914/00000/3662694E-1D4C-E511-8B6C-02163E0143E1.root'),
    lumisToProcess = cms.untracked.VLuminosityBlockRange("254231:1-254231:24", "254232:1-254232:81", "254790:90", "254790:93-254790:630", "254790:633-254790:697", 
        "254790:701-254790:715", "254790:719-254790:784", "254852:47-254852:94", "254879:52", "254879:54-254879:140", 
        "254906:1-254906:75", "254907:1-254907:52"),
    secondaryFileNames = cms.untracked.vstring()
)
process.AK8PFHT650TrimMass50 = cms.EDAnalyzer("RUNTriggerValidation",
    bits = cms.InputTag("TriggerResults","","HLT"),
    denomPath = cms.string('HLT_PFHT475'),
    hltPath = cms.string('HLT_AK8PFHT650_TrimR0p1PT0p03Mass50'),
    hltTrigger = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
    numerPath = cms.string('HLT_AK8PFHT650_TrimR0p1PT0p03Mass50'),
    objects = cms.InputTag("selectedPatTrigger"),
    orPath = cms.string('HLT_PFHT800'),
    prescales = cms.InputTag("patTrigger"),
    recoJets = cms.InputTag("slimmedJetsAK8")
)


process.p = cms.Path(process.AK8PFHT650TrimMass50)


process.MessageLogger = cms.Service("MessageLogger",
    FrameworkJobReport = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring('FwkJob', 
        'FwkReport', 
        'FwkSummary', 
        'Root_NoDictionary'),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(10000)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        optionalPSet = cms.untracked.bool(True),
        threshold = cms.untracked.string('INFO')
    ),
    cerr_stats = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        output = cms.untracked.string('cerr'),
        threshold = cms.untracked.string('WARNING')
    ),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    destinations = cms.untracked.vstring('warnings', 
        'errors', 
        'infos', 
        'debugs', 
        'cout', 
        'cerr'),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport'),
    infos = cms.untracked.PSet(
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        optionalPSet = cms.untracked.bool(True),
        placeholder = cms.untracked.bool(True)
    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    suppressDebug = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    )
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('RUNTriggerValidation_JetHT_Run2015C.root')
)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

