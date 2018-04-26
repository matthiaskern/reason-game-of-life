let strE = ReasonReact.string;

[@bs.val]
external requestAnimationFrame : (unit => unit) => int =
  "requestAnimationFrame";

[@bs.val] external cancelAnimationFrame : int => unit = "cancelAnimationFrame";

[@bs.val]
external viewportWidth : int = "document.documentElement.clientWidth";
