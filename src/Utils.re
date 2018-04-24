let strE = ReasonReact.stringToElement;

[@bs.val] external requestAnimationFrame : (unit => unit) => int =
  "requestAnimationFrame";

[@bs.val] external cancelAnimationFrame : int => unit = "cancelAnimationFrame"; 

[@bs.val] external viewportWidth : int = "document.documentElement.clientWidth"; 

