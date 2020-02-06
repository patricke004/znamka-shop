let s = ReasonReact.string;

let onBuy = (id, event) => Js.log(id);

module InsertOrderMutation = [%graphql {|
  mutation InsertOrderMutation($screamLevel: Int!) {
    scream(level: $screamLevel) {
      error
    }
  }
|}];

let handleConfirm = (id, email, plate) => {
  
};

[@react.component]
let make = (~tariffs) => {
  let (id, setId) = React.useState(() => None);
  let (plate, setPlate) = React.useState(() => "");
  let (email, setEmail) = React.useState(() => "");

  <div>
    <Table>
      <thead>
        <tr>
          <th>{s("#")}</th>
          <th>{s("Duration")}</th>
          <th>{s("Price")}</th>
          <th>{s("Currency")}</th>
        </tr>
      </thead>
      <tbody>
        {tariffs
          |> Array.mapi((i, tariff) =>
              <tr key={string_of_int(tariff##id)}>
                <td>{(i + 1)->string_of_int->s}</td>
                <td>{switch tariff##tariffDuration {
                | `monthly => s("Monthly")
                | `weekly => s("Weekly")
                | `yearly => s("Yearly")
                };}</td>
                <td>{tariff##price->string_of_int->s}</td>
                <td>{s(tariff##currencyByCurrency##currency_long)}</td>
                <td><Button onClick={_ => setId(_ => Some(tariff##id))}>{s("Buy")}</Button></td>
              </tr>
            )
          |> ReasonReact.array}
      </tbody>
    </Table>

    {switch id {
    | None => ReasonReact.null
    | Some(_) => 
      <div>
        <input value=plate onChange={e => setPlate(_ => e->ReactEvent.Form.currentTarget##value)} />
        <input value=email onChange={e => setEmail(_ => e->ReactEvent.Form.currentTarget##value)} />
        <Button onClick={_ => handleConfirm(id, email, plate)}>{s("Confirm")}</Button>
      </div>
    };}
  </div>;
};
