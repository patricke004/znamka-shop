module GetTarrifs = [%graphql
  {| query getTarrifs {
  tariffs {
    id
    currency
    currencyByCurrency {
      currency
      currency_long
    }
    price
    tariffDuration
  }
}
|}
];

module GetTarrifsQuery = ReasonApolloHooks.Query.Make(GetTarrifs);

[@react.component]
let make = () => {
  let (tariffs, _) = GetTarrifsQuery.use(~fetchPolicy=ReasonApolloHooks.Types.CacheAndNetwork, ());

  <>
    <PageHeading text="Znamka shop" />
    {switch tariffs {
    | NoData => <div>{React.string("No data")}</div>
    | Loading => <div>{React.string("Loading...")}</div>
    | Data(data) => <Tarrifs tariffs=data##tariffs />
    | Error(_) => <div>{React.string("There was an error fetching data")}</div>
    };}
  </>;
};
